#include "stdafx.h"

#include "aep_model\model\contexts\aep_model_assertion_context_impl.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

AssertionContextImpl::AssertionContextImpl( std::string const & _dutName )
	:	m_dutName( _dutName )
{
}

/***************************************************************************/

void 
AssertionContextImpl::addInstanceName( std::string const & _name )
{
	m_instances.push_back( _name );
}

/***************************************************************************/

void 
AssertionContextImpl::addChecker( OvlCheckerPtr _checker )
{
	m_checkers.push_back( std::move( _checker ) );
}

/***************************************************************************/

void 
AssertionContextImpl::forEachInstance( InstanceCallback _callback ) const
{
	std::for_each( m_instances.begin(), m_instances.end(), _callback );
}

/***************************************************************************/

}