#ifndef __VLOG_DM_WRITABLE_MULTIDIMENSIONAL_RANGE_HPP__
#define __VLOG_DM_WRITABLE_MULTIDIMENSIONAL_RANGE_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_multidimensional_range.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct MultidimensionalRange
	:	public VlogDM::MultidimensionalRange
{

/***************************************************************************/

	virtual void addRange( std::unique_ptr< Range > _range ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_WRITABLE_MULTIDIMENSIONAL_RANGE_HPP__
