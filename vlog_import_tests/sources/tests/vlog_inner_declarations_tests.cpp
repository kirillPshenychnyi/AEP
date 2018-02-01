#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_ports_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "simple inner wire", "[vars]" )
{
	std::string code =
		"module top (input a);	\n"
		"	wire c ;			\n"
		"endmodule				\n"
		;

	runImport( code );
}

/***************************************************************************/

}