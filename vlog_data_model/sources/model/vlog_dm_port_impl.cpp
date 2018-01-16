#include "stdafx.h"

#include "api\vlog_dm_dimension.hpp"

#include "sources\model\vlog_dm_port_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

PortImpl::PortImpl( 
		Declaration const & _declaration
	,	std::string const & _name
	,	Location const & _location
	,	std::unique_ptr<Dimension> _dimension
	,	PortDirection::Direction _direction 
	)
	:	BaseClass( 
				_declaration
			,	_name
			,	_location
			,	std::move( _dimension )
		)
	,	m_direction( _direction )
{
}

/***************************************************************************/

}
