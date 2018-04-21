
#include "stdafx.h"

#include "aep_model\model\accessor\aep_model_accessor.hpp"
#include "aep_model\model\checkers\aep_model_ovl_checkers_factory_impl.hpp"
#include "aep_model\model\contexts\aep_model_assertion_context_set_impl.hpp"
#include "aep_model\model\contexts\aep_model_assertion_context_impl.hpp"

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

AssertionContext & 
Accessor::addContext( std::string const & _dutName )
{
	auto context = std::make_unique< AssertionContextImpl >( _dutName );

	AssertionContext & ref = *context;

	m_contextSet->addContext( std::move( context ) );

	return ref;
}

/***************************************************************************/

}

/***************************************************************************/