#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_process_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple case statement", "[case_statement]" )
{
	std::string code =
		"module top (input a, output reg b );		\n"
		"	always@( * )							\n"
		"		case( a ) 							\n"
		"			1'b0: b = 1;					\n"
		"			1'b1: b = 0;					\n"
		"		endcase								\n"	
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 6 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple case statement with default", "[case_statement]" )
{
	std::string code =
		"module top (input a, output reg b );		\n"
		"	always@( * )							\n"
		"		case( a ) 							\n"
		"			1'b0: b = 1;					\n"
		"			1'b1: b = 0;					\n"
		"			default: b = a;					\n"
		"		endcase								\n"	
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 7 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple casex", "[case_statement]" )
{
	std::string code =
		"module top (input a, output reg b );		\n"
		"	always@( * )							\n"
		"	casex( a )								\n"
		"			1'b0: b = 1;					\n"
		"			1'b1: b = 0;					\n"
		"			default: b = a;					\n"
		"		endcase								\n"	
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 7 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple case statement with seq blocks", "[case_statement]" )
{
	std::string code =
		"module top (input a, output reg b, c );	\n"
		"	always@( * )							\n"
		"		case( a )							\n"
		"			1'b0: begin						\n"
		"				b = 1;						\n"
		"				c = 0;						\n"
		"			end								\n"
		"			1'b1: begin						\n"
		"				b = 0;						\n"
		"				c = 1;						\n"	
		"			end								\n"
		"			default: b = a;					\n"
		"		endcase								\n"	
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 13 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "case with non const labels", "[case_statement]" )
{
	std::string code =
		"module top (input a, b, c, output reg d );	\n"
		"	always@( * )							\n"
		"		case( a )							\n"
		"			b: d = 1;						\n"
		"			c: d = 0;						\n"
		"			default: d = a;					\n"
		"		endcase								\n"	
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 7 ) );
}

/***************************************************************************/

}
