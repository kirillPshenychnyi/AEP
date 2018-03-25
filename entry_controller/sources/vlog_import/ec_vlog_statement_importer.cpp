#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_statement_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_case_item_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_branch.hpp"
#include "vlog_data_model\api\vlog_dm_case_item.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_statement_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_conditional_statement.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_sequential_block.hpp"

#include <vector>

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

void 
StatementImporter::importStatement( 
	Verilog2001Parser::Statement_or_nullContext & ctx 
)
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
	ctx->delay_or_event_control()->accept( this );

	ctx->statement_or_null()->accept( this );

	RETURN_ANY
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

	RETURN_ANY
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

			RETURN_ANY
		}

		antlrcpp::Any visitStatement( 
			Verilog2001Parser::StatementContext * ctx 
		) override
		{
			m_statementImporter.importStatement( *ctx );
			m_statements.push_back( m_statementImporter.takeStatement() );

			RETURN_ANY
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

	RETURN_ANY
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
	idImporter.importIds( *ctx->variable_lvalue() );

	ExpressionImporter expressionImporter( getVlogDataModel() );

	m_resultStatement
		=	m_statementFactory.newBlockingAssignment(
				expressionFactory.newBinaryOperator(
						ExpressionImporter::createExpressionFromIds( 
								idImporter
							,	expressionFactory
							,	createLocation( *ctx )
						)
					,	expressionImporter.importExpression( *ctx->expression() )
					,	Operator::Kind::Assign
				)
			);

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
StatementImporter::visitSeq_block(
	Verilog2001Parser::Seq_blockContext * ctx
)
{
	StatementImporter importer( getVlogDataModel() );

	auto seqBlock = m_statementFactory.newSequentialBlock( createLocation( *ctx ) );

	forEachChildContext(
			*ctx
		,	[ & ]( antlr4::tree::ParseTree & _tree )
			{
				_tree.accept( &importer );
				importer.getControlsCount();

				if( importer.m_resultStatement )
					seqBlock->addStatement( importer.takeStatement() );
			}
	);

	m_resultStatement = std::move( seqBlock );

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
StatementImporter::visitCase_statement( 
	Verilog2001Parser::Case_statementContext * ctx 
)
{
	using namespace VlogDM;

	static const char * parallelCaseAttr = "parallel_case";
	static const char * fullCaseAttr = "full_case";

	IAccessor & accessor = getVlogDataModel();

	ExpressionImporter expressionImporter( getVlogDataModel() );

	auto caseStmt
		=	m_statementFactory.newCaseStatement( 
					createLocation( *ctx )
				,	expressionImporter.importExpression( *ctx->expression() )
				,	CaseKind::fromString( ctx->children.front()->getText().c_str() )
				,	m_statementAttributes.find( parallelCaseAttr ) != m_statementAttributes.end()
				,	m_statementAttributes.find( fullCaseAttr ) != m_statementAttributes.end()
			
		);

	CaseItemImporter itemImporter( getVlogDataModel() );

	for( auto item : ctx->case_item() )
		caseStmt->addBranch( itemImporter.importCaseItem( *item ) );

	m_resultStatement = std::move( caseStmt );

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any
StatementImporter::visitAttribute_instance( 
	Verilog2001Parser::Attribute_instanceContext * ctx
)
{
	for( auto attrSpec : ctx->attr_spec() )
		m_statementAttributes.insert( attrSpec->attr_name()->getText() );

	RETURN_ANY
}

/***************************************************************************/

}
}