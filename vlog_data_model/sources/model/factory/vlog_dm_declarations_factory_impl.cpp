#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_declarations_factory_impl.hpp"

#include "vlog_data_model\sources\model\vlog_dm_port_declaration_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_variable_declaration_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

Writable::PortDeclarationPtr
DeclarationsFactoryImpl::newPortDeclaration( 
		Location const & _location 
	,	TypePtr _type
	) const
{
	return std::make_unique< PortDeclarationImpl >( _location, std::move( _type ) );
}

/***************************************************************************/

Writable::VariableDeclarationPtr 
DeclarationsFactoryImpl::newVariableDeclaration( 
		Location const & _location 
	,	TypePtr _type
	) const
{
	return
		std::make_unique< VariableDeclarationImpl >( 
				_location
			,	std::move( _type ) 
		);
}

/***************************************************************************/

}