#ifndef __VLOG_DM_WRITABLE_CONCATENATION_HPP__
#define __VLOG_DM_WRITABLE_CONCATENATION_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_concatenation.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct Concatenation
	:	public VlogDM::Concatenation
{

/***************************************************************************/

	virtual void addExpression( ExpressionPtr _expression ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_WRITABLE_CONCATENATION_HPP__
