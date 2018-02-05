#include "stdafx.h"

#include "vlog_data_model\sources\model\vlog_dm_port_impl.hpp"

#include "vlog_data_model\api\vlog_dm_type.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_declared_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

PortImpl::PortImpl( 
		Declaration const & _declaration
	,	std::string const & _name
	,	Location const & _location
	,	std::unique_ptr< Dimension > _dimension
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

void 
PortImpl::accept( DeclaredVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}
