
#ifndef __VLOG_DM_DESIGN_UNIT_IMPL_HPP__
#define __VLOG_DM_DESIGN_UNIT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_process.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

#include "vlog_data_model\sources\model\vlog_dm_named_located_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_declarations_container_impl.hpp"

#include <vector>
#include <unordered_map>

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

class DesignUnitImpl
	: public NamedLocatedImpl< DeclarationsContainerImpl< Writable::DesignUnit > >
{

	/***************************************************************************/

	typedef
		NamedLocatedImpl< DeclarationsContainerImpl< Writable::DesignUnit > >
		BaseClass;

	typedef
		std::vector< ProcessPtr >
		Processes;

	typedef
		std::vector< std::string >
		InstancesNames;

	typedef
		std::unordered_map< std::string, InstancesNames >
		InstantiationTable;

	/***************************************************************************/

public:

	/***************************************************************************/

	DesignUnitImpl( std::string const & _name, Location const & _location );

/***************************************************************************/

	int getProcessesCount() const final;

	Process const & getProcess( int _idx ) const final;

	void addProcess( ProcessPtr _process ) final;

	void addChildInstance( 
			std::string const & _moduleName
		,	std::string const & _instanceName
	) final;

	void forEachChildInstance( 
			std::string const & _moduleName
		,	InstanceCallback _callback 
	) const final;

/***************************************************************************/

private:

/***************************************************************************/

	InstantiationTable m_instantiationTable;

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

inline 
void 
DesignUnitImpl::addChildInstance( 
		std::string const & _moduleName
	,	std::string const & _instanceName 
)
{
	auto findIt = m_instantiationTable.find( _moduleName );

	if( findIt == m_instantiationTable.end() )
		findIt = m_instantiationTable.emplace( _moduleName, InstancesNames() ).first;

	findIt->second.push_back( _instanceName );
}

/***************************************************************************/

inline 
void
DesignUnitImpl::forEachChildInstance( 
		std::string const & _moduleName
	,	InstanceCallback _callback 
) const
{
	auto it = m_instantiationTable.find( _moduleName );

	if( it != m_instantiationTable.end() )
		std::for_each( it->second.begin(), it->second.end(), _callback );
}

/***************************************************************************/

}

#endif // !__VLOG_DM_DESIGN_UNIT_IMPL_HPP__