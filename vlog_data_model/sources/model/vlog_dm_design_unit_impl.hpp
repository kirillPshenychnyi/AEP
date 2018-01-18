
#ifndef __VLOG_DM_DESIGN_UNIT_IMPL_HPP__
#define __VLOG_DM_DESIGN_UNIT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

#include "vlog_data_model\sources\model\vlog_dm_named_located_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_declarations_container_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

class DesignUnitImpl
	:	public NamedLocatedImpl< DeclarationsContainerImpl< Writable::DesignUnit > >
{

/***************************************************************************/

	typedef
		NamedLocatedImpl< DeclarationsContainerImpl< Writable::DesignUnit > >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	DesignUnitImpl( std::string const & _name, Location const & _location );

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_DESIGN_UNIT_IMPL_HPP__