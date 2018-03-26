
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

	int getProcessesCount() const final;

	Process const & getProcess( int _idx ) const final;

	void addProcess( ProcessPtr _process ) final;

/***************************************************************************/

private:

/***************************************************************************/

	Processes m_processes;

/***************************************************************************/

};

/***************************************************************************/

inline
DesignUnitImpl::DesignUnitImpl( 
		std::string const & _name
	,	Location const & _location )
	:	BaseClass( _name, _location )
{
}

/***************************************************************************/

inline
int 
DesignUnitImpl::getProcessesCount() const
{
	return m_processes.size();
}

/***************************************************************************/

inline
Process const & 
DesignUnitImpl::getProcess( int _idx ) const
{
	return *m_processes[ _idx ];
}

/***************************************************************************/

inline
void
DesignUnitImpl::addProcess( ProcessPtr _process )
{
	m_processes.push_back( std::move( _process ) );
}

/***************************************************************************/

}

#endif // !__VLOG_DM_DESIGN_UNIT_IMPL_HPP__