#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_statement_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_branch.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_statement_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_conditional_statement.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

StatementImporter::StatementImporter( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
	,	m_statementFactory( _accessor.getObjectFactory().getStatementFactory() )
{
}

/***************************************************************************/

void
StatementImporter::importStatement( Verilog2001Parser::StatementContext & ctx )
{
	visitEachChildContext( ctx );
}

/***************************************************************************/

VlogDM::StatementPtr 
StatementImporter::takeStatement()
{
	return std::move( m_resultStatement );
}

/***************************************************************************/

VlogDM::ExpressionPtr
StatementImporter::takeTimingControl( int _idx )
{
	return std::move( m_controls[ _idx ] );
}

/***************************************************************************/

int
StatementImporter::getControlsCount() const
{
	return m_controls.size();
}

/***************************************************************************/

antlrcpp::Any 
StatementImporter::visitProcedural_timing_control_statement(
	Verilog2001Parser::Procedural_timing_control_statementContext * ctx
)
{
	// first child is event context
	ctx->children[ 0 ]->accept( this );

	// second child is null or statement context
	ctx->children[ 1 ]->accept( this );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
StatementImporter::visitDelay_or_event_control(
	Verilog2001Parser::Delay_or_event_controlContext * ctx
)
{
	struct EventExpressionExtractor
		:	public Verilog2001BaseVisitor
	{
		typedef
			std::vector< Verilog2001Parser::ExpressionContext * >
			ExpressionContexts;

		EventExpressionExtractor()
		{
		}

		void extract( Verilog2001Parser::Delay_or_event_controlContext * ctx )
		{
			visitChildren( ctx );
		}

		antlrcpp::Any visitExpression(
			Verilog2001Parser::ExpressionContext * ctx
		) override
		{
			m_extracted.push_back( ctx );
			return defaultResult();
		}

		ExpressionContexts m_extracted;
	};

	EventExpressionExtractor extractor;
	extractor.extract( ctx );

	const int expressionsInTimingControl = extractor.m_extracted.size();
	for( int i = 0; i < expressionsInTimingControl; ++i )
	{ 
		ExpressionImporter expressionImporter( getVlogDataModel() );

		m_controls.push_back( 
			expressionImporter.importExpression( *extractor.m_extracted[ i ] ) 
		);
	}

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
StatementImporter::visitConditional_statement(
	Verilog2001Parser::Conditional_statementContext * ctx
)
{
	using namespace VlogDM;

	struct ConditionalStatementItemsExtractor
		:	public Verilog2001BaseVisitor
	{
		ConditionalStatementItemsExtractor( VlogDM::IAccessor & _vlogDm )
			:	m_expressionImporter( _vlogDm )
			,	m_statementImporter( _vlogDm )
		{
		}

		void extract( Verilog2001Parser::Conditional_statementContext const & _ctx )
		{
			for( auto child : _ctx.children )
				child->accept( this );
		}

		antlrcpp::Any visitExpression( 
			Verilog2001Parser::ExpressionContext * ctx 
		) override
		{
			m_branchesConditions.push_back( m_expressionImporter.importExpression( *ctx ) );

			return antlrcpp::Any();
		}

		antlrcpp::Any visitStatement( 
			Verilog2001Parser::StatementContext * ctx 
		) override
		{
			m_statementImporter.importStatement( *ctx );
			m_statements.push_back( m_statementImporter.takeStatement() );

			return antlrcpp::Any();
		}

		ExpressionImporter m_expressionImporter;
		StatementImporter m_statementImporter;

		ExpressionVector m_branchesConditions;
		StatementsVector m_statements;
	};

	ConditionalStatementItemsExtractor extractor( getVlogDataModel() );

	extractor.extract( *ctx );

	Writable::ConditionalStatementPtr conditionalStatement
		=	m_statementFactory.newConditionalStatement( createLocation( *ctx ) );

	const int condtionsCount = extractor.m_branchesConditions.size();
	const int statementsSize = extractor.m_statements.size();

	assert( condtionsCount <= statementsSize );

	for( int i = 0; i < condtionsCount; ++i )
	{
		conditionalStatement->addBranch(
			m_statementFactory.newConditionalBranch( 
					std::move( extractor.m_branchesConditions[ i ] )
				,	std::move( extractor.m_statements[ i ] )
			)
		);
	}

	// add 'else' branch
	if( statementsSize > condtionsCount )
	{
		conditionalStatement->addBranch(
			m_statementFactory.newConditionalBranch( 
					ExpressionPtr()
				,	std::move( extractor.m_statements[ statementsSize - 1 ] )
			)
		);
	}

	m_resultStatement = std::move( conditionalStatement );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
StatementImporter::visitBlocking_assignment(
	Verilog2001Parser::Blocking_assignmentContext * ctx
)
{
	using namespace VlogDM;

	Writable::ExpressionFactory const & expressionFactory 
		= getVlogDataModel().getObjectFactory().getExpressionFactory();

	IdentifierImporter idImporter( getVlogDataModel() );

	// first child is always var assign context
	idImporter.importIds(
		static_cast< Verilog2001Parser::Variable_assignmentContext const & >( 
			*ctx->children[ 0 ] 
		)
	);

	ExpressionImporter expressionImporter( getVlogDataModel() );

	// third child is always expression
	m_resultStatement
		=	m_statementFactory.newBlockingAssignment(
				expressionFactory.newBinaryOperator(
						ExpressionImporter::createExpressionFromIds( 
								idImporter
							,	expressionFactory
							,	createLocation( *ctx )
						)
					,	expressionImporter.importExpression(
							static_cast< Verilog2001Parser::ExpressionContext const & >( 
								*ctx->children[ 2 ] 
							)
						)
					,	Operator::Kind::Assign
				)
			);

	return antlrcpp::Any();
}

/***************************************************************************/

}
}