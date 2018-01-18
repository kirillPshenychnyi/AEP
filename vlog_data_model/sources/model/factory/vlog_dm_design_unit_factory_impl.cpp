
#include "stdafx.h"

#include "vlog_data_model/sources/model/factory/vlog_dm_design_unit_factory_impl.hpp"
#include "vlog_data_model/sources/model/vlog_dm_design_unit_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

std::unique_ptr< Writable::DesignUnit > 
DesignUnitFactoryImpl::newDesignUnit( 
		std::string const & _name
	,	Location const & _location 
	) const
{
	return std::make_unique< DesignUnitImpl >( _name, _location );
}

/***************************************************************************/
}