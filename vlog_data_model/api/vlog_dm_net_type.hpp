#ifndef __VLOG_DM_NET_TYPE_HPP__
#define __VLOG_DM_NET_TYPE_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_net_kind.hpp"
#include "vlog_data_model\api\vlog_dm_type.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct NetType
	:	public Type

{

/***************************************************************************/

	virtual NetKind::Kind getKind() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_NET_TYPE_HPP__
