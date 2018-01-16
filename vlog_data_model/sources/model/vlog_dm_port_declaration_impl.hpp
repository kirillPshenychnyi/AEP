#ifndef __VLOG_DM_PORT_DECLARATION_IMPL_HPP__
#define __VLOG_DM_PORT_DECLARATION_IMPL_HPP__

/***************************************************************************/

#include "ih\writable\vlog_dm_declaration.hpp"
#include "sources\model\vlog_dm_declaration_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class PortDeclarationImpl 
	:	public DeclarationImpl< Writable::PortDeclaration >
{

/***************************************************************************/

	typedef
		DeclarationImpl< Writable::PortDeclaration >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	PortDeclarationImpl( Location const & _location );

/***************************************************************************/

};

/***************************************************************************/

PortDeclarationImpl::PortDeclarationImpl( Location const & _location )
	:	BaseClass( _location )
{

}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_PORT_DECLARATION_IMPL_HPP__

