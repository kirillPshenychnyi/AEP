#ifndef __VLOG_IMPORT_PROCESS_FIXTURE_HPP__
#define __VLOG_IMPORT_PROCESS_FIXTURE_HPP__

/***************************************************************************/

#include "vlog_import_tests\sources\fixtures\vlog_import_base_module_items_fixture.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

class ProcessFixture
	:	public BaseModuleItemsFixture
{

/***************************************************************************/

public:

/***************************************************************************/

	ProcessFixture & expectDesignUnit( std::string const & _name, int _processCount );

	ProcessFixture & expectProcess( 
			int _idx
		,	BaseModuleItemsFixture::Lines const & _lines 
	);

/***************************************************************************/

private:

/***************************************************************************/

	const VlogDM::DesignUnit * m_designUnit;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_IMPORT_PROCESS_FIXTURE_HPP__
