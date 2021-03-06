#ifndef __VLOG_DM_DESIGN_UNIT_HPP__
#define __VLOG_DM_DESIGN_UNIT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\api\vlog_dm_named.hpp"

#include <functional>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct DesignUnit
	:	public DeclarationsContainer
	,	public Named
{

/***************************************************************************/

	typedef
		std::function< void( std::string ) >
		InstanceCallback;

/***************************************************************************/

	virtual int getProcessesCount() const = 0;

	virtual Process const & getProcess( int _idx ) const = 0;

	virtual void forEachChildInstance( 
			std::string const & _moduleName
		,	InstanceCallback _callback 
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DESIGN_UNIT_HPP__
