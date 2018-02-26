#ifndef __VLOG_DM_EXPRESSION_RANGE_HPP__
#define __VLOG_DM_EXPRESSION_RANGE_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_range.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace VlogDM
{

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
