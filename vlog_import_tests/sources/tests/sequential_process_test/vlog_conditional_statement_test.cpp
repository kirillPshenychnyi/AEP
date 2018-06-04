#include "stdafx.h"

#include "common_tools\catch.hpp"

#include "vlog_import_tests\sources\fixtures\vlog_import_process_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple if statement", "[conditional_statement]" )
{
	std::string code =
		"module top (input a, output reg b );	\n"
		"	always@( * )						\n"
		"		if( a == 0 )					\n"
		"			b = 0;						\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 4 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "if statement with else", "[conditional_statement]" )
{
	std::string code =
		"module top (input a, output reg b );	\n"
		"	always@( a )						\n"
		"		if( a == 0 )					\n"
		"			b = 0;						\n"
		"		else							\n"
		"			b = !a;						\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 6 ) );
}

/***************************************************************************/


TEST_CASE_METHOD( ProcessFixture, "couple signals in sensitity_list", "[conditional_statement]" )
{
	std::string code =
		"module top (input a, b, output reg c );	\n"
		"	always@( a, b )							\n"
		"		if( a == 0 )						\n"
		"			c = ( a | b );					\n"
		"		else								\n"
		"			c = 0;							\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 6 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "else_if branch", "[conditional_statement]" )
{
	std::string code =
		"module top (input a, b, output reg c );	\n"
		"	always@( a, b )							\n"
		"		if( a == 0 )						\n"
		"			c = ( a | b );					\n"
		"		else if( b == 1 )					\n"
		"			c = 0;							\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 6 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "else_if_else branch", "[conditional_statement]" )
{
	std::string code =
		"module top (input a, b, output reg c );	\n"
		"	always@( a, b )							\n"
		"		if( a == 0 )						\n"
		"			c = ( a | b );					\n"
		"		else if( b == 1 )					\n"
		"			c = 0;							\n"
		"		else								\n"
		"			c = 1;							\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 8 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "nested if", "[conditional_statement]" )
{
	std::string code =
		"module top (input a, b, output reg c );	\n"
		"	always@( a, b )							\n"
		"		if( a == 0 )						\n"
		"			if( b == 1 )					\n"
		"				c = ( a | b );				\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 5 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "branch with couple statements", "[conditional_statement]" )
{
	std::string code =
		"module top (input a, output reg b, c );	\n"
		"	always@( a, b )							\n"
		"		if( a == 0 )						\n"
		"		begin								\n"
		"			b = !a;							\n"
		"			c = a;							\n"
		"		end									\n"	
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 7 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "else branch with couple statements", "[conditional_statement]" )
{
	std::string code =
		"module top (input a, output reg b, c );	\n"
		"	always@( a, b )							\n"
		"		if( a == 0 )						\n"
		"		begin								\n"
		"			b = a;							\n"
		"			c = !a;							\n"
		"		end									\n"
		"		else								\n"
		"		begin								\n"
		"			b = !a;							\n"
		"			c = a;							\n"
		"		end									\n"	
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 12 ) );
}

/***************************************************************************/

}