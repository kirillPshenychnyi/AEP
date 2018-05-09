#ifndef __VLOG_DM_RANGE_VISITOR_HPP__
#define __VLOG_DM_RANGE_VISITOR_HPP__

/***************************************************************************/

#include "common_tools\utils\declare_visitors.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct Range;
	struct ExpressionRange;
	struct PartSelectRange;
	struct MultidimensionalRange;

/***************************************************************************/

DECLARE_VISITORS( Range, ExpressionRange, PartSelectRange, MultidimensionalRange )

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_RANGE_VISITOR_HPP__
