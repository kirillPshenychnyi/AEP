#include "stdafx.h"

#include "sources\model\factory\vlog_dm_declared_factory_impl.hpp"
#include "sources\model\vlog_dm_port_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

std::unique_ptr<Port>
DeclaredFactoryImpl::newPort( 
		Declaration const & _declaration
	,	std::string const & _name
	,	Location const & _location
	,	PortDirection::Direction _direction
	,	NetType::Type _type
	,	std::unique_ptr< Dimension > _dimension 
) const
{	
	return
		std::make_unique< PortImpl >(
				_declaration
			,	_name
			,	_location
			,	std::unique_ptr<Dimension>( _dimension.release() )
			,	_direction
			,	_type
		);
}

/***************************************************************************/

}