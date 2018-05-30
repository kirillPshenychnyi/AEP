#ifndef __VLOG_DM_WHILE_LOOP_IMPL_HPP__
#define __VLOG_DM_WHILE_LOOP_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_while_loop.hpp"

#include "vlog_data_model\sources\model\vlog_dm_conditional_loop_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class WhileLoopImpl
	:	public ConditionalLoopImpl< WhileLoop >
{

/***************************************************************************/

	typedef
		ConditionalLoopImpl< WhileLoop >
		BaseClass;

	using BaseClass::BaseClass;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_WHILE_LOOP_IMPL_HPP__
