#include "stdafx.h"

#include "aep_test\fixtures\aep_test_ovl_checker_helper.hpp"

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_port.hpp"

#include "common_tools\catch.hpp"

/***************************************************************************/

namespace AepTest {

/***************************************************************************/

OvlCheckerHelper::OvlCheckerHelper( 
		AepModel::OvlChecker const & _checker
	,	AssertionContextHelper & _parent
)
	:	m_checker( _checker )
	,	m_parent( _parent )
	,	m_innerWireInfoHelper( std::make_unique< InnerWireInfoHelper > ( *this ) )
{
}

/***************************************************************************/

OvlCheckerHelper & 
OvlCheckerHelper::id( AepModel::OvlCheckerIds::Kind _id )
{
	return check( m_checker.getId(), _id );	
}

/***************************************************************************/

OvlCheckerHelper &
OvlCheckerHelper::instanceName( std::string const & _instName )
{
	return check( m_checker.getInstanceName(), _instName );
}

/***************************************************************************/

OvlCheckerHelper & 
OvlCheckerHelper::suspectLine( int _line )
{	
	return check( m_checker.getSuspectCodeLine(), _line );
}

/***************************************************************************/

OvlCheckerHelper & 
OvlCheckerHelper::ports( int _portsCount )
{
	return check( m_checker.getPortsCount(), _portsCount );
}

/***************************************************************************/

OvlCheckerHelper & 
OvlCheckerHelper::port( 
		AepModel::OvlCheckerPortKind::Kind _portKind
	,	std::string const & _value
) 
{
	auto portOpt = m_checker.getPort( _portKind );

	REQUIRE( portOpt.is_initialized() );

	return check( portOpt->getValue(), _value );
}

/***************************************************************************/

OvlCheckerHelper &
OvlCheckerHelper::genericsParameters( int _genericsCount )
{
	return check( m_checker.getGenericsCount(), _genericsCount );
}

/***************************************************************************/

OvlCheckerHelper::InnerWireInfoHelper &
OvlCheckerHelper::innerWires()
{
	return *m_innerWireInfoHelper;
}

/***************************************************************************/

AssertionContextHelper & 
OvlCheckerHelper::end()
{
	return m_parent;
}

/***************************************************************************/

template< typename _TParameter >
OvlCheckerHelper & 
OvlCheckerHelper::check( 
		_TParameter const & _actual
	,	_TParameter const & _expected
)
{
	REQUIRE( _actual == _expected );

	return *this;
}

/***************************************************************************/

}