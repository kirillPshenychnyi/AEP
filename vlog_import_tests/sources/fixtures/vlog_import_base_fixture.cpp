
#include "stdafx.h"

#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

#include "entry_controller\sources\ec_accessor.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

void 
BaseFixture::runImport( std::string const & _code )
{
	EntryController::Accessor::getInstance().importVerilog( _code );
}

/***************************************************************************/

}
