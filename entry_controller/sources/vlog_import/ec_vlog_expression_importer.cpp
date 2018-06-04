#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_unary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_multiple_concatenation.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_expression.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_concatenation.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

ExpressionImporter::ExpressionImporter( 
		VlogDM::IAccessor & _vlogDm 
	,	Errors::IImportErrorsSet & _errorsSet 
)
	:	BaseImporter( _vlogDm, _errorsSet )
	,	m_expressionFactory( _vlogDm.getObjectFactory().getExpressionFactory() )
{
}

/***************************************************************************/

VlogDM::ExpressionPtr
ExpressionImporter::importExpression( 
	Verilog2001Parser::ExpressionContext const & _expression 
)
{
	reset();

	visitEachChildContext( _expression );

	createExpression();

	return std::move( m_result );
}

/***************************************************************************/

VlogDM::ExpressionPtr 
ExpressionImporter::createExpressionFromIds(
		IdentifierImporter & _importer 
	,	VlogDM::Writable::ExpressionFactory const & _expressionFactory
	,	VlogDM::Location const & _idLocation
)
{
	using namespace VlogDM;

	auto primaryIdCreator
		=	[ & ]( int _idx ) -> ExpressionPtr
			{
				return _expressionFactory.newPrimaryIdentifier( _importer.takeId( _idx ) );
			};
	
	const int idsCount = _importer.getIdsCount();

	if( idsCount == 1 )
		return primaryIdCreator( 0 );

	auto concat = _expressionFactory.newConcatenation( _idLocation );

	for( int i = 0; i < idsCount; ++i )
		concat->addExpression( primaryIdCreator( i ) );

	return std::move( concat );	
}

/***************************************************************************/

void
ExpressionImporter::createExpression()
{
	using namespace VlogDM;

	if( m_result )
		return;

	if( m_topNodes.empty() )
	{
		m_result = getLastContext().getValidOperand();

		return;
	}

	OperatorInfo & lastContex = getLastContext();

	if( ExpressionPtr validOperand = lastContex.getValidOperand() )
	{
		m_topNodes.push_back( std::move( validOperand ) );
		m_operators.push_back( lastContex.m_operator );
	}

	if( m_topNodes.size() == 1 )
	{
		ExpressionPtr operand = std::move( m_topNodes.front() );
		Location const & location = operand->getLocation();

		if( m_operators.empty() )
			m_result = std::move( operand );
		else 
		{
			assert( m_operators.size() == 1 );

			m_result = 
				m_expressionFactory.newUnaryOperator(
						std::move( operand )
					,	m_operators.front()
					,	location
				);
		}
	
		return;
	}

	while( true )
	{
		buildTopBinaryNodes( m_topNodes );
		
		if( m_topNodes.size() == 1 )
		{
			m_result = std::move( m_topNodes.front() );
			break;
		}
	}
}

/***************************************************************************/

void 
ExpressionImporter::buildTopBinaryNodes( Operands & _primaryNodes )
{
	using namespace VlogDM;

	OperatorInfo info( m_operators.front() );
	Operands binaryNodes;

	m_operators.pop_front();
	const int topNodesCount = _primaryNodes.size();

	for( int i = 0; i < topNodesCount; ++i )
	{
		info.addOperand( std::move( _primaryNodes[ i ] ) );

		if( info.canConstructBinaryOperator() )
			binaryNodes.push_back( createBinaryOperator( info ) );
	}

	if( ExpressionPtr lastOperand = info.getValidOperand() )
	{
		assert( m_operators.size() == 1 );

		info.addOperand( std::move( binaryNodes.back() ) );
		info.addOperand( std::move( lastOperand ) );
		info.m_operator = m_operators.front();

		binaryNodes.pop_back();					
		binaryNodes.push_back( createBinaryOperator( info ) );
	}

	_primaryNodes = std::move( binaryNodes );
}

/***************************************************************************/

VlogDM::ExpressionPtr 
ExpressionImporter::createBinaryOperator( OperatorInfo & _info )
{
	using namespace VlogDM;
			
	ExpressionPtr binaryOp
		=	m_expressionFactory.newBinaryOperator(
					std::move( _info.m_leftOperand )
				,	std::move( _info.m_rightOperand )
				,	_info.m_operator
			);

	_info.clear();

	return binaryOp;
}

/***************************************************************************/

VlogDM::ExpressionPtr 
ExpressionImporter::createUnaryOperator( OperatorInfo & _info )
{
	using namespace VlogDM;
			
	Location const & location = _info.m_leftOperand->getLocation();

	ExpressionPtr unaryOp
		=	m_expressionFactory.newUnaryOperator(
					_info.getValidOperand()
				,	_info.m_operator
				,	location
			);

	return unaryOp;
}

/***************************************************************************/

VlogDM::ConcatPtr 
ExpressionImporter::createConcat( 
	Verilog2001Parser::ConcatenationContext & _concateContext 
)
{
	using namespace VlogDM;
	
	auto concat 
		=	m_expressionFactory.newConcatenation( 
				createLocation( _concateContext ) 
			);

	ExpressionImporter importer( takeVlogDataModel(), takeErrorsSet() );
	for( auto expression : _concateContext.expression() )
		concat->addExpression( importer.importExpression( *expression ) );

	return std::move( concat );
}

/***************************************************************************/

void
ExpressionImporter::processLastContext()
{
	using namespace VlogDM;

	OperatorInfo & lastContext = getLastContext();

	if( lastContext.canConstructBinaryOperator() )
	{
		m_topNodes.push_back( createBinaryOperator( lastContext ) );

		m_contexts.pop_back();
	}
	else if( lastContext.canConstructUnaryOperator() )
	{
		ExpressionPtr unaryOp = createUnaryOperator( lastContext );

		m_contexts.pop_back();

		if( !m_contexts.empty() )
			m_contexts.back().addOperand( std::move( unaryOp ) );
		else 
			m_topNodes.push_back( std::move( unaryOp ) );
	}
}

/***************************************************************************/

ExpressionImporter::OperatorInfo &
ExpressionImporter::getLastContext()
{
	if( m_contexts.empty() )
		m_contexts.push_back( OperatorInfo() );

	return m_contexts.back();
}

/***************************************************************************/

void 
ExpressionImporter::reset()
{
	m_contexts.clear();
	m_operators.clear();
	m_topNodes.clear();
	m_result.reset();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitPrimary( Verilog2001Parser::PrimaryContext * ctx )
{
	using namespace VlogDM;

	visitEachChildContext( *ctx );

	processLastContext();

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitExpression( Verilog2001Parser::ExpressionContext * ctx )
{
	using namespace VlogDM;

	OperatorInfo & lastContext = getLastContext();

	if( !Operator::isUnary( lastContext.m_operator ) )
		visitEachChildContext( *ctx );
	else 
	{
		ExpressionImporter expressionImporter( takeVlogDataModel(), takeErrorsSet() );
		
		lastContext.addOperand( expressionImporter.importExpression( *ctx ) );
	}

	processLastContext();

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitBinary_operator(
	Verilog2001Parser::Binary_operatorContext * ctx
)
{
	OperatorInfo & lastContext = getLastContext();

	if( lastContext.m_operator != VlogDM::Operator::Kind::Unknown )
		m_operators.push_back( lastContext.m_operator );

	lastContext.m_operator
		= VlogDM::Operator::fromString( ctx->getText().c_str() );

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitUnary_operator( Verilog2001Parser::Unary_operatorContext * ctx )
{
	m_contexts.push_back( 
		OperatorInfo( VlogDM::Operator::fromString( ctx->getText().c_str() ) ) 
	);

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitNumber( Verilog2001Parser::NumberContext * ctx )
{
	getLastContext().addOperand( 
		m_expressionFactory.newPrimaryLiteral(
				createLocation( *ctx )
			,	ctx->getText() 
		) 
	);

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitSimple_hierarchical_identifier( 
	Verilog2001Parser::Simple_hierarchical_identifierContext * ctx 
)
{
	IdentifierImporter idImporter( takeVlogDataModel(), takeErrorsSet() );

	idImporter.importId( *ctx );

	if( idImporter.getIdsCount() != 0 )
	{
		getLastContext().addOperand(
			m_expressionFactory.newPrimaryIdentifier(
				idImporter.takeId( 0 )
			)
		);
	}

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any
ExpressionImporter::visitConcatenation(
	Verilog2001Parser::ConcatenationContext * ctx
) 
{
	m_result = createConcat( *ctx );

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitMultiple_concatenation( 
	Verilog2001Parser::Multiple_concatenationContext * ctx 
)
{
	using namespace VlogDM;

	ExpressionImporter importer( takeVlogDataModel(), takeErrorsSet() );

	m_result = 
		m_expressionFactory.newMultipleConcatenation(
				importer.importExpression( *ctx->constant_expression()->expression() )
			,	createConcat( *ctx->concatenation() )
			,	createLocation( *ctx )
		);

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitConditional_operator( 
	Verilog2001Parser::Conditional_operatorContext * ctx 
)
{
	using namespace VlogDM;

	static const int conditionItemPosition = 0;
	static const int trueBranchItemPosition = 2;
	static const int falseBranchItemPosition = 4;

	auto importConditionalOperatorItem
		=	[ & ]( int _idx )
			{
				ctx->children[ _idx ]->accept( this );
				createExpression();	

				return std::move( m_result );
			};
	
	m_result = 
		m_expressionFactory.newConditionalExpression(
				createLocation( *ctx )
			,	importConditionalOperatorItem( conditionItemPosition )
			,	importConditionalOperatorItem( trueBranchItemPosition )
			,	importConditionalOperatorItem( falseBranchItemPosition )
		);

	RETURN_ANY
}

/***************************************************************************/

}
}