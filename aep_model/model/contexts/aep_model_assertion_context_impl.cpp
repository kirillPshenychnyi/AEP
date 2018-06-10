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

OvlChecker const & 
AssertionContextImpl::getChecker( int _idx ) const
{
	return *m_checkers.at( _idx );
}

void
AssertionContextImpl::forEachInstance( InstanceCallback _callback ) const
{
	std::for_each( m_instances.begin(), m_instances.end(), _callback );
}

/***************************************************************************/

void 
AssertionContextImpl::forEachInputPort( InputPortCallback _callback ) const
{
	for( PortInfo const & info : m_additionaInputs )
		_callback( info );
}

/***************************************************************************/

void 
AssertionContextImpl::forEachChecker( CheckerCallback _callback ) const
{
	for( auto const & checker : m_checkers )
		_callback( *checker );
}

/***************************************************************************/

void 
AssertionContextImpl::addInputPort( 
		std::string const&  _portName 
	,	std::string const& _portValue
	,	int _width  
)
{
	m_additionaInputs.emplace( _portName, _portValue, _width );
}

/***************************************************************************/

}