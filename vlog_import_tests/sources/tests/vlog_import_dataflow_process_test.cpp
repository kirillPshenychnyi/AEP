#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( BaseFixture, "simple dataflow process", "[dataflow]" )
{
	std::string code =
		"module top (input a, output b );	\n"
		"	assign a = b;					\n"
		"endmodule							\n"
		;

	runImport( code );
}

/***************************************************************************/

}