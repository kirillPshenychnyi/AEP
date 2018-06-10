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
	return check( m_checker.getId(), _id, "checker id" );	
}

/***************************************************************************/

OvlCheckerHelper &
OvlCheckerHelper::instanceName( std::string const & _instName )
{
	return check( m_checker.getInstanceName(), _instName, "instance name" );
}

/***************************************************************************/

OvlCheckerHelper & 
OvlCheckerHelper::suspectLine( int _line )
{	
	return check( m_checker.getSuspectCodeLine(), _line, "suspect line"  );
}

/***************************************************************************/

OvlCheckerHelper & 
OvlCheckerHelper::ports( int _portsCount )
{
	return check( m_checker.getPortsCount(), _portsCount, "ports count" );
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

	return 
		check( 
				portOpt->getValue()
			,	_value
			,	"port value"
		);
}

/***************************************************************************/

OvlCheckerHelper &
OvlCheckerHelper::genericsParameters( int _genericsCount )
{
	return check( m_checker.getGenericsCount(), _genericsCount, "generics count" );
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
	,	std::string const & _paramName
)
{
	if( _actual != _expected )
		FAIL( _paramName + " mistmatch" );

	return *this;
}

/***************************************************************************/

}