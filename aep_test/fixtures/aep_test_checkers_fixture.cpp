#include "stdafx.h"

#include "aep_test\fixtures\aep_test_checkers_fixture.hpp"
#include "entry_controller\sources\ec_accessor.hpp"
#include "vlog_data_model\sources\model\vlog_dm_accessor.hpp"
#include "aep\sources\accessor\aep_accessor.hpp"
#include "aep_model\model\accessor\aep_model_accessor.hpp"

#include "common_tools\catch.hpp"

/***************************************************************************/

namespace AepTest {

/***************************************************************************/

CheckersFixture::CheckersFixture( Aep::CheckerIds _id )
	:	m_checkerId( _id )
{
	m_vlogDm = std::make_shared< VlogDM::Accessor >();
	m_aepModel = std::make_shared< AepModel::Accessor >();	
	m_aep = std::make_shared< Aep::Accessor >( m_vlogDm, m_aepModel ) ;	
	m_entryController = std::make_shared< EntryController::Accessor >( m_vlogDm, m_aep );
}

/***************************************************************************/

void
CheckersFixture::run( 
		std::string const & _code
	,	Aep::IAccessor::GlobalClockParameters const & _clk
	,	boost::optional < Aep::IAccessor::GlobalResetParameters const & > _reset 
)
{
	m_vlogDm->reset();
	m_aepModel->reset();

	REQUIRE( m_entryController->importVerilog( _code ) );

	m_aep->runEngine( m_checkerId, _clk, _reset );
}

/***************************************************************************/

void 
CheckersFixture::contextsCount( int _expected )
{
	REQUIRE( m_aepModel->getContextsCount() == _expected );
}

/***************************************************************************/

AssertionContextHelper & 
CheckersFixture::expectContext( std::string const & _module )
{
	auto context = m_aepModel->getAssertionContext( _module );

	REQUIRE( context.is_initialized() );

	m_contextHelper.reset( new AssertionContextHelper( *context ) );

	return *m_contextHelper;
}

/***************************************************************************/

}