#include "stdafx.h"

#include "common_tools\catch.hpp"

#include "vlog_import_tests\sources\fixtures\vlog_import_errors_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( ImportErrorsFixture, "missing token error", "[errors]" )
{
	std::string code =
		"module top (input a, output b );	\n"
		"	assign b = a					\n"
		"endmodule							\n"
	;

	runImport( code );

	expectErrors( 1 )
		.syntaxError( 3 );
}

/***************************************************************************/

TEST_CASE_METHOD( ImportErrorsFixture, "wrong operator", "[errors]" )
{
	std::string code =
		"module top (input a, b, output c );	\n"
		"	assign c = b ? a 1'b0;				\n"
		"endmodule								\n"
	;

	runImport( code );

	expectErrors( 3 )
		.syntaxError( 2 )
		.syntaxError( 2 )
		.syntaxError( 2 );
}

/***************************************************************************/

TEST_CASE_METHOD( ImportErrorsFixture, "undeclared id", "[errors]" )
{
	std::string code =
		"module top (input a, b, output c );	\n"
		"	assign c = a + c1;					\n"
		"endmodule								\n"
	;

	runImport( code );

	expectErrors( 1 )
		.undeclaredId( 2, "c1" );
}

/***************************************************************************/

TEST_CASE_METHOD( ImportErrorsFixture, "undeclared ids", "[errors]" )
{
	std::string code =
		"module top ();							\n"
		"	assign a = b + c;					\n"
		"endmodule								\n"
	;

	runImport( code );

	expectErrors( 3 )
		.undeclaredId( 2, "a" )
		.undeclaredId( 2, "b" )
		.undeclaredId( 2, "c" );
}

/***************************************************************************/

TEST_CASE_METHOD( ImportErrorsFixture, "undeclared id and syntax error", "[errors]" )
{
	std::string code =
		"module top ( output a );				\n"
		"	assign a = b + c +					\n"
		"endmodule								\n"
	;

	runImport( code );

	expectErrors( 3 )
		.syntaxError( 3 )
		.undeclaredId( 2, "b" )
		.undeclaredId( 2, "c" );
}

/***************************************************************************/

}

/***************************************************************************/