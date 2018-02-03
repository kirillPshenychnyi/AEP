#ifndef __VLOG_DM_VARIABLE_HPP__
#define __VLOG_DM_VARIABLE_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_declared.hpp"
#include "vlog_data_model\api\vlog_dm_dimensional.hpp"
#include "vlog_data_model\api\vlog_dm_port_directrion.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Variable
	:	public Declared
	,	public Dimensional
{

/***************************************************************************/

	virtual bool isSigned() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_VARIABLE_HPP__
