
#ifndef __VLOG_DM_DESIGN_UNIT_IMPL_HPP__
#define __VLOG_DM_DESIGN_UNIT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_design_unit.hpp"

#include "vlog_data_model\sources\model\vlog_dm_named_located_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

class DesignUnitImpl
	:	public NamedLocatedImpl< DesignUnit >
{

/***************************************************************************/

	typedef
		NamedLocatedImpl< DesignUnit >
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