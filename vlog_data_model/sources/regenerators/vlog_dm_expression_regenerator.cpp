#include "stdafx.h"

#include "vlog_data_model\sources\regenerators\vlog_dm_expression_regenerator.hpp"
#include "vlog_data_model\sources\regenerators\vlog_dm_range_regenerator.hpp"

#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_unary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"
#include "vlog_data_model\api\vlog_dm_concatenation.hpp"
#include "vlog_data_model\api\vlog_dm_multiple_concatenation.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_expression.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators {

/***************************************************************************/

ExpressionRegenerator::ExpressionRegenerator( std::ostream & _targetStream )
	:	BaseRegenerator( _targetStream )
{
}

/***************************************************************************/

void 
ExpressionRegenerator::visit( const PrimaryLiteral& _literal )
{
	m_targetStream << _literal.getValue();
}

/***************************************************************************/

void 
ExpressionRegenerator::visit( const BinaryOperator& _operator )
{
	const bool isAssign 
		= _operator.getOperator() == VlogDM::Operator::Kind::Assign;

	if( !isAssign )
		m_targetStream << "( ";

	_operator.getLeftOperand().accept( *this );

	m_targetStream 
		<< ' ' << Operator::toString( _operator.getOperator() ) << ' ';

	_operator.getRightOperand().accept( *this );

	if( !isAssign )
		m_targetStream << " )";
}

/***************************************************************************/

void 
ExpressionRegenerator::visit( const UnaryOperator& _operator )
{
	m_targetStream << Operator::toString( _operator.getOperator() );

	_operator.getOperand().accept( *this );
}

/***************************************************************************/

void 
ExpressionRegenerator::visit( const PrimaryIdentifier& _id )
{
	m_targetStream << _id.getIdentifier().getName();

	if( auto range = _id.getIdentifier().getRange() )
	{
		RangeRegenerator rangeRegenerator( m_targetStream );

		range->accept( rangeRegenerator );
	}
}

/***************************************************************************/

void 
ExpressionRegenerator::visit( Concatenation const& _concat )
{
	const int itemsCount = _concat.getExpressionsCount();

	m_targetStream << "{ ";

	bool isLast;
	for( int i = 0; i < itemsCount; ++i )
	{
		_concat.getExpression( i ).accept( *this );

		isLast = i == itemsCount - 1;

		if( !isLast )
			m_targetStream << ", ";
	}

	m_targetStream << " }";
}

/***************************************************************************/

void 
ExpressionRegenerator::visit( MultipleConcatenation const& _concat )
{
	m_targetStream << "{ ";

	_concat.getRepeatExpression().accept( *this );
	_concat.getConcatenation().accept( *this );

	m_targetStream << " }";
}

/***************************************************************************/

void 
ExpressionRegenerator::visit( ConditionalExpression const & _conditional )
{
	_conditional.getCondition().accept( *this );

	m_targetStream << " ? ";

	_conditional.getTrueBranch().accept( *this );

	m_targetStream << " : ";

	_conditional.getFalseBranch().accept( *this );
}

/***************************************************************************/

}
}