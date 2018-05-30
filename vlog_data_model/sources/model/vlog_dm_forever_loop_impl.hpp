#ifndef __VLOG_DM_FOREVER_LOOP_IMPL_HPP__
#define __VLOG_DM_FOREVER_LOOP_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_loop_impl.hpp"
#include "vlog_data_model\api\vlog_dm_forever_loop.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ForeverLoopImpl
	:	public LoopImpl< ForeverLoop >
{

/***************************************************************************/

	typedef
		LoopImpl< ForeverLoop >
		BaseClass;

public:

/***************************************************************************/

	using BaseClass::BaseClass;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_FOREVER_LOOP_IMPL_HPP__
