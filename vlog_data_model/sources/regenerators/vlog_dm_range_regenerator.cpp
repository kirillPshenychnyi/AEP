#include "stdafx.h"

#include "vlog_data_model\sources\regenerators\vlog_dm_range_regenerator.hpp"
#include "vlog_data_model\sources\regenerators\vlog_dm_expression_regenerator.hpp"

#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_part_select_range.hpp"
#include "vlog_data_model\api\vlog_dm_expression_range.hpp"
#include "vlog_data_model\api\vlog_dm_multidimensional_range.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators {

/***************************************************************************/

RangeRegenerator::RangeRegenerator( std::ostream & _targetStream )
	:	BaseRegenerator( _targetStream )
{
}

/***************************************************************************/

void 
RangeRegenerator::visit( ExpressionRange const & _range )
{
	m_targetStream << "[ ";

	ExpressionRegenerator expressionRegenerator( m_targetStream );

	_range.getExpression().accept( expressionRegenerator );

	m_targetStream << " ]";
}

/***************************************************************************/

void
RangeRegenerator::visit( PartSelectRange const & _range )
{
}

/***************************************************************************/

void 
RangeRegenerator::visit( MultidimensionalRange const & _range )
{
}

/***************************************************************************/

}
}