#include "stdafx.h"

#include "vlog_data_model\sources\vlog_engines\vlog_dm_expression_bitwidth_calculator.hpp"
#include "vlog_data_model\sources\vlog_engines\vlog_dm_range_bitwidth_processor.hpp"

#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"

#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_unary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_multiple_concatenation.hpp"
#include "vlog_data_model\api\vlog_dm_concatenation.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_expression.hpp"
#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_variable.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_declaration.hpp"
#include "vlog_data_model\api\vlog_dm_type.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_declared_visitor.hpp"

/***************************************************************************/

namespace VlogDM {
namespace VlogEngines {

/***************************************************************************/

const int ExpressionBitwidthCalculator::m_sSingleBitWidth = 1;

/***************************************************************************/

ExpressionBitwidthCalculator::ExpressionBitwidthCalculator()
	:	m_result( 0 )
{
}

/***************************************************************************/

int 
ExpressionBitwidthCalculator::calculate( Expression const & _expression )
{
	_expression.accept( *this );

	return m_result;
}

/***************************************************************************/

void
ExpressionBitwidthCalculator::visit( PrimaryLiteral const & _literal )
{
	try
	{
		int value = std::stoi( _literal.getValue() );
		int numOfBits = 1;
		
		while( value )
		{
		  value &= value - 1;
		  numOfBits++;
		}

		m_result = numOfBits;
	}
	catch( std::exception const & /*_ex*/ )
	{

	}
}

/***************************************************************************/

void
ExpressionBitwidthCalculator::visit( BinaryOperator const & _operator )
{
	switch( _operator.getOperator() )
	{
		case Operator::Kind::Plus:
		case Operator::Kind::Minus:
		case Operator::Kind::Div:
		case Operator::Kind::Mul:
		case Operator::Kind::And:
		case Operator::Kind::Xor:
		case Operator::Kind::Or:
			calculateMaxOfBinary( _operator );
			break;
		default:
			m_result = m_sSingleBitWidth;
			break;
	}
}

/***************************************************************************/

void
ExpressionBitwidthCalculator::visit( UnaryOperator const & _operator )
{
	switch( _operator.getOperator() )
	{
		case Operator::Kind::Plus:
		case Operator::Kind::Minus:
		case Operator::Kind::Not:
		case Operator::Kind::LogicNot:
			_operator.getOperand().accept( *this );
			break;
		default:
			m_result = m_sSingleBitWidth;
			break;
	}
}

/***************************************************************************/

void
ExpressionBitwidthCalculator::visit( PrimaryIdentifier const & _id )
{	
	if( auto range = _id.getIdentifier().getRange() )
	{
		RangeBitwidthProcessor rangeProc;
		m_result = rangeProc.calculate( *range );
		return;
	}
	
	m_result = calculateDeclared( _id.getIdentifier().getDeclared() );
}

/***************************************************************************/

void
ExpressionBitwidthCalculator::visit( Concatenation const & _concat )
{
	const int nExpressions = _concat.getExpressionsCount();

	ExpressionBitwidthCalculator calc;

	for( int i = 0; i < nExpressions; ++i )
		m_result += calc.calculate( _concat.getExpression( i ) );
}

/***************************************************************************/

void
ExpressionBitwidthCalculator::visit( MultipleConcatenation const & _concat )
{
	_concat.getConcatenation().accept( *this );
}

/***************************************************************************/

void
ExpressionBitwidthCalculator::visit( ConditionalExpression const & _conditional )
{
	_conditional.getFalseBranch().accept( *this );
	int falseBranchWidth = m_result;
	
	reset();

	_conditional.getTrueBranch().accept( *this );
	int trueBranchWidth = m_result;

	m_result = std::max( falseBranchWidth, trueBranchWidth );
	
}

/***************************************************************************/

int 
ExpressionBitwidthCalculator::calculateDeclared( Declared const & _declared )
{
	struct DeclaredDimensionExctactor
		:	public DeclaredVisitor
	{
		boost::optional< Dimension const& > extract( Declared const & _declared )
		{
			_declared.accept( *this );

			return m_dimension;
		}

		void visit( Port const& _port ) final
		{
			m_dimension = _port.getDimension();
		}

		void visit( Variable const& _var ) final
		{
			m_dimension = _var.getDimension();
		}

		boost::optional< Dimension const& > m_dimension;
	};

	RangeBitwidthProcessor rangeProc;

	int typeWidth = 1;
	if( auto dimension = _declared.getDeclaration().getType().getDimension() )
	{
		typeWidth = rangeProc.calculate( dimension->getRange() );
	}

	DeclaredDimensionExctactor dimensionExtractor;
	int elementsCount = 1;
	if( auto dimension = dimensionExtractor.extract( _declared ) )
	{
		elementsCount = rangeProc.calculate( dimension->getRange() );
	}

	return elementsCount * typeWidth;
}

/***************************************************************************/

void
ExpressionBitwidthCalculator::calculateMaxOfBinary( BinaryOperator const & _binary )
{
	 _binary.getLeftOperand().accept( *this );

	 int leftOperandWidth = m_result;

	reset();

	_binary.getRightOperand().accept( *this );

	int rightOperandWidth = m_result;

	m_result = std::max( leftOperandWidth, rightOperandWidth );
}

/***************************************************************************/

void 
ExpressionBitwidthCalculator::reset()
{
	m_result = 0;
}

/***************************************************************************/

}
}