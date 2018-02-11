#ifndef __VLOG_DM_DESIGN_UNIT_FACTORY_IMPL_HPP__
#define __VLOG_DM_DESIGN_UNIT_FACTORY_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_design_unit_factory.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/
	
class DesignUnitFactoryImpl 
	:	public Writable::DesignUnitFactory
{

/***************************************************************************/
		
public:

/***************************************************************************/

	Writable::DesignUnitPtr newDesignUnit( 
			std::string const & _name
		,	Location const & _location 
	) const override;

/***************************************************************************/

};

/***************************************************************************/
}

#endif 