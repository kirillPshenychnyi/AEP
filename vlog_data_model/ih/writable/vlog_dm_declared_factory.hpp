#ifndef __VLOG_DM_DECLARED_FACTORY_HPP__
#define __VLOG_DM_DECLARED_FACTORY_HPP__

/***************************************************************************/

#include "boost\noncopyable.hpp"

#include "vlog_data_model\api\vlog_dm_port_directrion.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"

/***************************************************************************/

namespace VlogDM
{
	struct Declaration;
	struct Location;
	struct Type;

	struct Port;
	struct Dimension;
}

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct DeclaredFactory 
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual std::unique_ptr< Port > newPort ( 
			VlogDM::Declaration const & _declaration
		,	std::unique_ptr< Type > _type
		,	std::string const & _name
		,	Location const & _location
		,	PortDirection::Direction _direction
		,	std::unique_ptr< Dimension > _dimension
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // __VLOG_DM_DECLARED_FACTORY_HPP__