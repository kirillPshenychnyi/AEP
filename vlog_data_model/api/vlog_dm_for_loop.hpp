#ifndef __VLOG_DM_FOR_LOOP_HPP__
#define __VLOG_DM_FOR_LOOP_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_loop.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct ForLoop
	:	public Loop
{

/***************************************************************************/

	virtual Expression const & getInitialization() const = 0;

	virtual Expression const & getCondition() const = 0;

	virtual BinaryOperator const & getIteration() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_FOR_LOOP_HPP__
