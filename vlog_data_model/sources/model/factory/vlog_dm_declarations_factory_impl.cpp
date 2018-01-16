#include "stdafx.h"

#include "sources\model\factory\vlog_dm_declarations_factory_impl.hpp"

#include "sources\model\vlog_dm_port_declaration_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

std::unique_ptr< Writable::PortDeclaration > 
DeclarationsFactoryImpl::newPortDeclaration( Location const & _location ) const
{
	return std::unique_ptr<Writable::PortDeclaration>( new PortDeclarationImpl( _location ) );
}

/***************************************************************************/

}