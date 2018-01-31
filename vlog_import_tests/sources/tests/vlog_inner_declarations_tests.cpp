#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_ports_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "simple inner wire", "[ports]" )
{
	std::string code =
		"module top (input a);	\n"
		"	NOT u1 (a);			\n"
		"endmodule				\n"
		;

	runImport( code );
}

/***************************************************************************/

}