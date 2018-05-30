#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_process_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple for statement", "[loops]" )
{
	std::string code =
		"module top (input a, output reg b );	\n"
		"	integer i;							\n"
		"	always@( * )						\n"
		"	for( i = 0; i < 10; i = i + 1 )		\n"
		"		if( a == 0 )					\n"
		"			b = 0;						\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 3, 6 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "for statement with couple loop stmt", "[loops]" )
{
	std::string code =
		"module top (input a, output reg b, c );\n"
		"	integer i;							\n"
		"	always@( * )						\n"
		"	for( i = 0; i < 10; i = i + 1 )		\n"
		"	begin								\n"
		"		b = 0;							\n"
		"		c = !a;							\n"
		"	end									\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 3, 8 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple while loop", "[loops]" )
{
	std::string code =
		"module top (input a, output reg b, c );\n"
		"	integer i;							\n"
		"	i = 10;								\n"
		"	always@( * )						\n"
		"	while ( i < 0 )						\n"
		"	begin								\n"
		"		b = 0;							\n"
		"		c = !a;							\n"
		"		i = ( i - 1 );					\n"
		"	end									\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 4, 10 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "if within while loop", "[loops]" )
{
	std::string code =
		"module top (input a, output reg b, c );\n"
		"	integer i;							\n"
		"	i = 10;								\n"
		"	always@( * )						\n"
		"	while ( i < 0 )						\n"
		"	begin								\n"
		"		if( b == 0 )					\n"
		"			c = !a;						\n"
		"		i = ( i - 1 );					\n"
		"	end									\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 4, 10 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "repeat loop", "[loops]" )
{
	std::string code =
		"module top (input a, output reg b, c );\n"
		"	integer i;							\n"
		"	i = 10;								\n"
		"	always@( * )						\n"
		"	repeat ( i < 0 )					\n"
		"	begin								\n"
		"		if( b == 0 )					\n"
		"			c = !a;						\n"
		"		i = ( i - 1 );					\n"
		"	end									\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 4, 10 ) );
}

/***************************************************************************/


TEST_CASE_METHOD( ProcessFixture, "forever loop", "[loops]" )
{
	std::string code =
		"module top (input a, output reg b, c );\n"
		"	integer i;							\n"
		"	i = 10;								\n"
		"	always@( * )						\n"
		"	forever								\n"
		"	begin								\n"
		"		if( b == 0 )					\n"
		"			c = !a;						\n"
		"		i = ( i - 1 );					\n"
		"	end									\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 4, 10 ) );
}

/***************************************************************************/

}