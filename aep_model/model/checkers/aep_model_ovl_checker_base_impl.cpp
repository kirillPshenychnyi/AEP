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
OvlCheckerImpl::getGeneric( GenericType::Kind _type ) const
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
	auto value = getPort( _type );

	assert( value );

	value->setValue( _value );
}

/***************************************************************************/

boost::optional< OvlCheckerPort& >
OvlCheckerImpl::getPort( OvlCheckerPortKind::Kind _type ) const
{
	auto value = m_ports.find( _type, CheckerPortHasher(), CheckerPortComparator() );
	
	return
			value == m_ports.end()
		?	boost::optional< OvlCheckerPort & >()
		:	**value;
}

/***************************************************************************/

void 
OvlCheckerImpl::setPortAsWire( 
		OvlCheckerPortKind::Kind _type
	,	std::string const & _lhs
	,	std::string const & _rhs
	,	int _width 
)
{
	m_innerWires.emplace_back( _lhs, _rhs, _width );

	setPort( _type, _lhs );
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

void 
OvlCheckerImpl::foreachPort( PortCallback const & _functor ) const
{
	for( auto const & port : m_ports )
		_functor( *port );
}

/***************************************************************************/

void 
OvlCheckerImpl::foreachInnerWire( InnerWireCallback const & _functor ) const
{
	for( auto const & item : m_innerWires )
		_functor( item );
}

/***************************************************************************/

}

/***************************************************************************/