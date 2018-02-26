#include "stdafx.h"
#include "vlog_data_model\sources\model\vlog_dm_design_unit_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

DesignUnitImpl::DesignUnitImpl( std::string const & _name, Location const & _location )
	:	BaseClass( _name, _location )
{
}

/***************************************************************************/

int 
DesignUnitImpl::getProcessesCount() const
{
	return m_processes.size();
}

/***************************************************************************/

Process const & 
DesignUnitImpl::getProcess( int _idx ) const
{
	return *m_processes[ _idx ];
}

/***************************************************************************/

void
DesignUnitImpl::addProcess( ProcessPtr _process )
{
	m_processes.push_back( std::move( _process ) );
}

/***************************************************************************/

}

