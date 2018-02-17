#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

ExpressionImporter::ExpressionImporter( 
		VlogDM::IAccessor & _vlogDm 
	,	VlogDM::Writable::DesignUnit const & _targetUnit
	)
	:	BaseImporter( _vlogDm )
	,	m_targetUnit( _targetUnit )
{
}

/***************************************************************************/

VlogDM::ExpressionPtr
ExpressionImporter::importExpression( Verilog2001Parser::ExpressionContext & _expression )
{
	using namespace VlogDM;

	acceptEachChildContext( _expression );

	return createExpression();
}

/***************************************************************************/

VlogDM::RangePtr 
ExpressionImporter::importRange( 
	Verilog2001Parser::Range_expressionContext & _rangeExpression 
)
{
	acceptEachChildContext( _rangeExpression );

	return 
		getVlogDataModel().getItemsFactory().newExpressionRange( 
			createExpression()
		);
}

/***************************************************************************/

VlogDM::ExpressionPtr 
ExpressionImporter::createExpression()
{
	using namespace VlogDM;

	if( m_topNodes.empty() )
		return m_currentInfo.getValidOperand();

	if( ExpressionPtr validOperand = m_currentInfo.getValidOperand() )
	{
		m_topNodes.push_back( std::move( validOperand ) );
		m_operators.push_back( m_currentInfo.m_operator );
	}

	if( m_topNodes.size() == 1 )
		return std::move( m_topNodes.front() );

	Writable::ExpressionFactory const & expressionFactory 
			= getVlogDataModel().getExpressionFactory();

	auto buildTopBinaryNodes
		=	[ this ]( Operands & _primaryNodes )
			{
				BinaryOperatoInfo info;
				Operands binaryNodes;
				const int topNodesCount = _primaryNodes.size();

				for( int i = 0; i < topNodesCount; ++i )
				{
					info.addOperand( std::move( _primaryNodes[ i ] ) );

					if( info.canConstructBinaryOperator() )
					{
						info.m_operator = m_operators.front();
						m_operators.pop_front();
						binaryNodes.push_back( createBinaryOperator( info ) );
					}
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
			};

	while( true )
	{
		buildTopBinaryNodes( m_topNodes );
		
		if( m_topNodes.size() == 1 )
			return std::move( m_topNodes.front() );
	}

	return VlogDM::ExpressionPtr();
}

/***************************************************************************/

VlogDM::ExpressionPtr 
ExpressionImporter::createBinaryOperator( BinaryOperatoInfo & _info )
{
	using namespace VlogDM;
			
	Writable::ExpressionFactory const & expressionFactory 
		=	getVlogDataModel().getExpressionFactory();

	ExpressionPtr binaryOp
		=	expressionFactory.newBinaryOperator(
					std::move( _info.m_leftOperand )
				,	std::move( _info.m_rightOperand )
				,	_info.m_operator
			);

	_info.clear();

	return std::move( binaryOp );
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitTerm( Verilog2001Parser::TermContext * ctx )
{
	acceptEachChildContext( *ctx );
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitPrimary( Verilog2001Parser::PrimaryContext * ctx )
{
	using namespace VlogDM;

	acceptEachChildContext( *ctx );

	if( m_currentInfo.canConstructBinaryOperator() )
		m_topNodes.push_back( createBinaryOperator( m_currentInfo ) );
	
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitBinary_operator(
	Verilog2001Parser::Binary_operatorContext * ctx
)
{
	if( m_currentInfo.m_operator != VlogDM::Operator::Kind::Unknown )
		m_operators.push_back( m_currentInfo.m_operator );

	m_currentInfo.m_operator = VlogDM::Operator::fromString( ctx->getText().c_str() );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitNumber( Verilog2001Parser::NumberContext * ctx )
{
	m_currentInfo.addOperand( 
		getVlogDataModel().getExpressionFactory().newPrimaryLiteral(
				createLocation( *ctx )
			,	ctx->getText() 
		) 
	);

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitSimple_hierarchical_identifier( 
	Verilog2001Parser::Simple_hierarchical_identifierContext * ctx 
	)
{
	using namespace VlogDM;

	IAccessor & vlogDM = getVlogDataModel();

	auto declared = m_targetUnit.findDeclared( ctx->getText() );

	IdentifierImporter idImporter( getVlogDataModel(), m_targetUnit );

	idImporter.importId( *ctx );

	m_currentInfo.addOperand( 
			vlogDM.getExpressionFactory().newPrimaryIdentifier( 
					idImporter.takeId( 0 )
			)
	);

	return antlrcpp::Any();
}

/***************************************************************************/

}
}