#ifndef __VLOG_DM_DESIGN_UNIT_FACTORY_HPP__
#define __VLOG_DM_DESIGN_UNIT_FACTORY_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct DesignUnitFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual DesignUnitPtr newDesignUnit( 
			std::string const & _name
		,	Location const & _location 
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_DESIGN_UNIT_FACTORY_HPP__

