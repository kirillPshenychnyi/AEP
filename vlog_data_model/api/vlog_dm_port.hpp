#ifndef __VLOG_DM_PORT_HPP__
#define __VLOG_DM_PORT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_declared.hpp"
#include "vlog_data_model\api\vlog_dm_dimensional.hpp"
#include "vlog_data_model\api\vlog_dm_port_directrion.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

struct Port
	:	public Declared
	,	public Dimensional
{

/***************************************************************************/

	virtual PortDirection::Direction getDirection() const = 0;
	
	virtual NetType::Type getNetType() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_PORT_HPP__
