#include "stdafx.h"

#include "vlog_data_model\sources\regenerators\vlog_dm_expression_regenerator.hpp"
#include "vlog_data_model\sources\regenerators\vlog_dm_range_regenerator.hpp"

#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"

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
	_operator.getLeftOperand().accept( *this );

	m_targetStream << ' ' << Operator::toString( _operator.getOperator() ) << ' ';

	_operator.getRightOperand().accept( *this );

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

}
}