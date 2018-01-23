#ifndef __VLOG_DM_PART_SELECT_RANGE_HPP__
#define __VLOG_DM_PART_SELECT_RANGE_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_range.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

struct Expression;

/***************************************************************************/

struct PartSelectRange
	:	public Range
{

/***************************************************************************/

	virtual Expression const & getRightBound() const = 0;

	virtual Expression const & getLeftBound() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_PART_SELECT_RANGE_HPP__

