#include "stdafx.h"

#include "vlog_import_tests\sources\fixtures\vlog_import_process_fixture.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_design_unit.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

ProcessFixture & 
ProcessFixture::expectDesignUnit( std::string const & _name, int _processesCount )
{
	auto unit = getVlogDm().findUnit( _name );

	REQUIRE( unit.is_initialized() );

	REQUIRE( unit->getProcessesCount() == _processesCount );

	m_designUnit = unit.get_ptr();

	return *this;
}

/***************************************************************************/

ProcessFixture &
ProcessFixture::expectProcess( 
		int _idx
	,	BaseModuleItemsFixture::Lines const & _lines  
)
{
	REQUIRE( _idx < m_designUnit->getProcessesCount() );

	std::stringstream stream;

	getVlogDm().regenerateProcess( stream, m_designUnit->getProcess( _idx ) );

	checkCorrectImport( stream.str(), _lines );

	return *this;
}

/***************************************************************************/

}