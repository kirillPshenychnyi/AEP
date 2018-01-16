#ifndef __VLOG_DM_EXPRESSION_RANGE_HPP__
#define __VLOG_DM_EXPRESSION_RANGE_HPP__

/***************************************************************************/

#include "api\vlog_dm_range.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

struct Expression;

/***************************************************************************/

struct ExpressionRange
	:	public Range
{

/***************************************************************************/

	virtual Expression const & getExpression() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_EXPRESSION_RANGE_HPP__