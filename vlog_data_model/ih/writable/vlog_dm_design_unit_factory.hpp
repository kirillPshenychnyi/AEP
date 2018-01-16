#ifndef __VLOG_DM_DESIGN_UNIT_FACTORY_HPP__
#define __VLOG_DM_DESIGN_UNIT_FACTORY_HPP__

/***************************************************************************/

#include "boost\noncopyable.hpp"

/***************************************************************************/

namespace VlogDM
{
	struct DesignUnit;
	struct Location;
}

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct DesignUnitFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual ~DesignUnitFactory() {}

	virtual std::unique_ptr< DesignUnit > newDesignUnit( 
			std::string const & _name
		,	Location const & _location 
	) = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_DESIGN_UNIT_FACTORY_HPP__

