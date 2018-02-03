#ifndef __VLOG_IMPORT_VARIABLES_FIXTURE_HPP__
#define __VLOG_IMPORT_VARIABLES_FIXTURE_HPP__

/***************************************************************************/

#include "vlog_import_tests\sources\fixtures\vlog_import_test_base_net_fixture.hpp"

#include "vlog_data_model\api\vlog_dm_variable.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

class VariablesFixture
	:	public BaseNetFixture< VlogDM::Variable >
{

};

}

/***************************************************************************/

#endif // !__VLOG_IMPORT_VARIABLES_FIXTURE_HPP__
