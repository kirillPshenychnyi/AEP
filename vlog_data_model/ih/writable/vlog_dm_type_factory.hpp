#ifndef __VLOG_DM_TYPE_FACTORY_HPP__
#define __VLOG_DM_TYPE_FACTORY_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "vlog_data_model\api\vlog_dm_net_kind.hpp"
#include "vlog_data_model\api\vlog_dm_variable_kind.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct NetType;
struct VariableType;
struct Dimension;

/***************************************************************************/

}

/***************************************************************************/

namespace VlogDM {
namespace Writable { 

/***************************************************************************/

struct TypeFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual std::unique_ptr< NetType > newNetType(
			NetKind::Kind _netKind
		,	std::unique_ptr< Dimension > _dimension
	) const = 0;

	virtual std::unique_ptr< VariableType > newVariableType(
			VariableKind::Kind _netKind
		,	std::unique_ptr< Dimension > _dimension
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_TYPE_FACTORY_HPP__
