#ifndef __VLOG_DM_PART_SELECT_RANGE_HPP__
#define __VLOG_DM_PART_SELECT_RANGE_HPP__

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

	virtual Expression const & getRightExpression() const = 0;

	virtual Expression const & getLeftExpression() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_PART_SELECT_RANGE_HPP__

