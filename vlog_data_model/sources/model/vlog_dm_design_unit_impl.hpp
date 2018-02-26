
#ifndef __VLOG_DM_DESIGN_UNIT_IMPL_HPP__
#define __VLOG_DM_DESIGN_UNIT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_process.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

#include "vlog_data_model\sources\model\vlog_dm_named_located_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_declarations_container_impl.hpp"

#include <vector>

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

	typedef
		std::vector< ProcessPtr >
		Processes;

/***************************************************************************/

public:

/***************************************************************************/

	DesignUnitImpl( std::string const & _name, Location const & _location );

/***************************************************************************/

	int getProcessesCount() const override;

	Process const & getProcess( int _idx ) const override;

	void addProcess( ProcessPtr _process ) override;

/***************************************************************************/

private:

/***************************************************************************/

	Processes m_processes;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_DESIGN_UNIT_IMPL_HPP__