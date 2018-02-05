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

	Writable::PortDeclarationPtr newPortDeclaration( 
			Location const & _location 
		,	TypePtr  _type
	) const override;

	Writable::VariableDeclarationPtr newVariableDeclaration( 
			Location const & _location 
		,	TypePtr _type
	) const override;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_DECLARATIONS_FACTORY_IMPL_HPP__
