#ifndef __VLOG_DM_MULTIDIMENSIOANAL_RANGE_HPP__
#define __VLOG_DM_MULTIDIMENSIOANAL_RANGE_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_range.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

struct MultidimensionalRange
	:	public Range
{

/***************************************************************************/

	virtual int getRangesCount() const = 0;

	virtual Range const & getRange( int _idx ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_MULTIDIMENSIOANAL_RANGE_HPP__
