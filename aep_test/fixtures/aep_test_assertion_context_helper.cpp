#include "stdafx.h"

#include "aep_test\fixtures\aep_test_assertion_context_helper.hpp"

/***************************************************************************/

namespace AepTest {

/***************************************************************************/

AssertionContextHelper::AssertionContextHelper( 
	AepModel::AssertionContext const & _context 
)
	:	m_context( _context )
{}

/***************************************************************************/

AssertionContextHelper::InstanceHelper & 
AssertionContextHelper::instances()
{
	m_instanceHelper.reset( new InstanceHelper( *this ) );

	return *m_instanceHelper;
}

/***************************************************************************/

AssertionContextHelper::PortHelper & 
AssertionContextHelper::ports()
{
	m_portHelper.reset( new PortHelper( *this ) );

	return *m_portHelper;
}

/***************************************************************************/

OvlCheckerHelper & 
AssertionContextHelper::checker( int _checker )
{
	
	m_checkerHelper.reset(
		new OvlCheckerHelper( m_context.getChecker( _checker ), *this )
	);

	return *m_checkerHelper;
}

/***************************************************************************/

}