#ifndef __VLOG_DM_WRITABLE_SENSITIVITY_LIST_HPP__
#define __VLOG_DM_WRITABLE_SENSITIVITY_LIST_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_sensitivity_list.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct SensitivityList
	:	public VlogDM::SensitivityList
{

/***************************************************************************/

	virtual void addExpression( ExpressionPtr _expression ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_WRITABLE_SENSITIVITY_LIST_HPP__
