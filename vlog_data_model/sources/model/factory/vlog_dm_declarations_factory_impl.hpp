#ifndef __VLOG_DM_DECLARATIONS_FACTORY_IMPL_HPP__
#define __VLOG_DM_DECLARATIONS_FACTORY_IMPL_HPP__

/***************************************************************************/

#include "ih\writable\vlog_dm_declaration_factory.hpp"

/***************************************************************************/

namespace VlogDM { 

/***************************************************************************/

class DeclarationsFactoryImpl
	:	public Writable::DeclarationFactory
{

/***************************************************************************/

public:

/***************************************************************************/

	std::unique_ptr< Writable::PortDeclaration > newPortDeclaration( 
			Location const & _location 
	) const override;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_DECLARATIONS_FACTORY_IMPL_HPP__
