#include "stdafx.h"

#include "aep_model\model\checkers\aep_model_ovl_checker_base_impl.hpp"

#include "common_tools\utils\convertors.hpp"

/***************************************************************************/

namespace AepModel { 

/***************************************************************************/

OvlCheckerImpl::OvlCheckerImpl( 
		OvlCheckerIds::Kind _id
	,	std::string const & _instanceName
	,	std::string const & _moduleFileName
	,	int _suspectLine 
)
	:	m_id( _id )
	,	m_instanceName( _instanceName )
	,	m_moduleFileName( _moduleFileName )
	,	m_suspectLine( _suspectLine )
{
}

/***************************************************************************/

boost::optional< OvlCheckerGenericParameter& > 
OvlCheckerImpl::getParameter( GenericType::Kind _type ) const
{
	auto value = m_generics.find( _type, GenericParamHasher(), GenericParamComparator() );
	
	return
			value == m_generics.end()
		?	boost::optional< OvlCheckerGenericParameter & >()
		:	**value;
}

/***************************************************************************/

void 
OvlCheckerImpl::addParameter( 
	std::unique_ptr< OvlCheckerGenericParameter > _parameter 
)
{
	m_generics.insert( std::move( _parameter ) );
}

/***************************************************************************/

void 
OvlCheckerImpl::setPort( 
		OvlCheckerPortKind::Kind _type
	,	std::string const & _value 
)
{
}

/***************************************************************************/

boost::optional< OvlCheckerPort& >
OvlCheckerImpl::getPort( OvlCheckerPortKind::Kind _type ) const
{
	auto value = m_ports.find( _type, CheckerPortHasher(), CheckerPortComparator() );
	return boost::optional< OvlCheckerPort & >();
	
	return
			value == m_ports.end()
		?	boost::optional< OvlCheckerPort & >()
		:	**value;
}

/***************************************************************************/

void
OvlCheckerImpl::addPort( std::unique_ptr< OvlCheckerPort > _port )
{
	m_ports.insert( std::move( _port ) );
}

/***************************************************************************/

void
OvlCheckerImpl::foreachGeneric( GenericParameterCallback const & _functor ) const
{
	for( auto const & item : m_generics )
		_functor( *item );
}

/***************************************************************************/

}

/***************************************************************************/