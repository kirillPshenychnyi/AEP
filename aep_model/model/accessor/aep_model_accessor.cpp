
#include "stdafx.h"

#include "aep_model\model\accessor\aep_model_accessor.hpp"
#include "aep_model\model\checkers\aep_model_ovl_checkers_factory_impl.hpp"
#include "aep_model\model\contexts\aep_model_assertion_context_set_impl.hpp"
#include "aep_model\model\contexts\aep_model_assertion_context_impl.hpp"

#include "aep_model\model\contexts\regeneration\aep_model_context_set_regenerator.hpp"

#include <fstream>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

Accessor::Accessor()
	:	m_checkersFactory( std::make_unique< OvlCheckersFactoryImpl >() )
	,	m_contextSet( std::make_unique< AssertionContextSetImpl >() )
{
}

/***************************************************************************/

boost::optional< AssertionContext & >
Accessor::takeAssertionContext( std::string const & _dutName )
{
	return m_contextSet->takeContext( _dutName );
}

/***************************************************************************/

boost::optional< AssertionContext const& >
Accessor::getAssertionContext( std::string const & _dutName )
{
	return m_contextSet->getContext( _dutName );
}

/***************************************************************************/

AssertionContext & 
Accessor::addContext( std::string const & _dutName )
{
	auto context = std::make_unique< AssertionContextImpl >( _dutName );

	AssertionContext & ref = *context;

	m_contextSet->addContext( std::move( context ) );

	return ref;
}

/***************************************************************************/

void 
Accessor::forEachContext( AssertionContextCallback _callback )
{
	m_contextSet->forEachAssertionContext( _callback );
}

/***************************************************************************/

void
Accessor::forEachContext( ConstAssertionContextCallback _callback ) const
{
	m_contextSet->forEachAssertionContext( _callback );
}

/***************************************************************************/

void 
Accessor::regenerateAssertions( std::string const & _path ) const
{
	std::fstream stream;

	stream.open( "e:\\Education\\aep_generated\\aep.sv", std::ios::out );

	ContextSetRegenerator regenerator( *m_contextSet, stream );	

	regenerator.run();

	stream.close();
}

/***************************************************************************/

}

/***************************************************************************/