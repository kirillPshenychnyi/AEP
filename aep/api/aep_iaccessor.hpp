#ifndef __AEP_IACCESSOR_HPP__
#define __AEP_IACCESSOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "aep_model\api\aep_model_fwd.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

struct IAccessor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void runEngine() = 0; 

	virtual VlogDM::IAccessor const & getVlogDm() const = 0;

	virtual AepModel::IAccessor & getAepModel() = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_IACCESSOR_HPP__
