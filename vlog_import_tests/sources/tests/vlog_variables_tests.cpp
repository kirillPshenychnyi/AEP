#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_test_variables_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "simple wire var", "[vars]" )
{
	std::string code =
		"module top (input a );	\n"
		"	wire c ;			\n"
		"endmodule				\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "c" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "simple reg var", "[vars]" )
{
	std::string code =
		"module top (input a );	\n"
		"	reg	 c ;			\n"
		"endmodule				\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "c" )
			.expectRegType()
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "one declaration couple wires", "[vars]" )
{
	std::string code =
		"module top ();		\n"
		"	wire a, b, c;	\n"
		"endmodule			\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end()
		.expectNet( "b" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end()
		.expectNet( "c" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "one declaration couple regs", "[vars]" )
{
	std::string code =
		"module top ();		\n"
		"	reg a, b, c;	\n"
		"endmodule			\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectRegType()
		.end()
		.expectNet( "b" )
			.expectRegType()
		.end()
		.expectNet( "c" )
			.expectRegType()
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "two declaration couple vars", "[vars]" )
{
	std::string code =
		"module top ();		\n"
		"	reg a, b;		\n"
		"	wire c;			\n"
		"endmodule			\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectRegType()
		.end()
		.expectNet( "b" )
			.expectRegType()
		.end()
		.expectNet( "c" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "separate declarations for each var", "[vars]" )
{
	std::string code =
		"module top ();		\n"
		"	reg a;			\n"
		"	wire d;			\n"
		"	reg b;			\n"
		"	wire c;			\n"
		"endmodule			\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectRegType()
		.end()
		.expectNet( "b" )
			.expectRegType()
		.end()
		.expectNet( "c" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end()
		.expectNet( "d" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "wire bus", "[vars]" )
{
	std::string code =
		"module top ();		\n"
		"	wire [3:0] a;	\n"
		"endmodule			\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
			.expectBounds( RANGE( 3, 0 ) )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "couple buses", "[vars]" )
{
	std::string code =
		"module top ();			\n"
		"	wire [3:0] a, b;	\n"
		"endmodule				\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
			.expectBounds( RANGE( 3, 0 ) )
		.end()
		.expectNet( "b" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
			.expectBounds( RANGE( 3, 0 ) )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "simple wire array", "[vars]" )
{
	std::string code =
		"module top ();		\n"
		"	wire a[3:0];	\n"
		"endmodule			\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectNetType( VlogDM::NetKind::Kind::wire )
			.expectArrayBounds( RANGE( 3, 0 ) )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "simple memory", "[vars]" )
{
	std::string code =
		"module top ();			\n"
		"	reg [7:0] a[3:0];	\n"
		"endmodule				\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectRegType()
			.expectBounds( RANGE( 7, 0 ) )
			.expectArrayBounds( RANGE( 3, 0 ) )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "multidimensional wor", "[vars]" )
{
	std::string code =
		"module top ();			\n"
		"	wor a [3:0][1:0];	\n"
		"endmodule				\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectNetType( VlogDM::NetKind::Kind::wor )
			.expectArrayBounds( { RANGE( 3, 0 ), RANGE( 1, 0 ) } )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "multidimensional memory", "[vars]" )
{
	std::string code =
		"module top ();				\n"
		"	reg [7:0] a [7:0][0:3];	\n"
		"endmodule					\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectRegType()
			.expectBounds( RANGE( 7, 0 ) )
			.expectArrayBounds( { RANGE( 7, 0 ), RANGE( 0, 3 ) } )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "simple reg and array wihin one declaration", "[vars]" )
{
	std::string code =
		"module top ();		 \n"
		"	reg a, b[0:7];	 \n"
		"endmodule			 \n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectRegType()
		.end()
		.expectNet( "b" )
			.expectRegType()
			.expectArrayBounds( RANGE( 0, 7 ) )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "different arrays wihin one declaration", "[vars]" )
{
	std::string code =
		"module top ();				    \n"
		"	reg a [7:0][0:3], b[0:10];	\n"
		"endmodule					    \n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectRegType()
			.expectArrayBounds( { RANGE( 7, 0 ), RANGE( 0, 3 ) } )
		.end()
		.expectNet( "b" )
			.expectRegType()
			.expectArrayBounds( RANGE( 0, 10 ) )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "arrays and scalar wihin one declaration", "[vars]" )
{
	std::string code =
		"module top ();				            \n"
		"	reg  a, b[7:0][0:3], c[0:10];	    \n"
		"endmodule					            \n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectRegType()
		.end()
		.expectNet( "b" )
			.expectRegType()
			.expectArrayBounds( { RANGE( 7, 0 ), RANGE( 0, 3 ) } )
		.end()
		.expectNet( "c" )
			.expectRegType()
			.expectArrayBounds( RANGE( 0, 10 ) )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( VariablesFixture, "arrays and scalar wihin one declaration", "[vars]" )
{
	std::string code =
		"module top ();				            \n"
		"	reg  a, b[7:0][0:3], c[0:10];	    \n"
		"endmodule					            \n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectNet( "a" )
			.expectRegType()
		.end()
		.expectNet( "b" )
			.expectRegType()
			.expectArrayBounds( { RANGE( 7, 0 ), RANGE( 0, 3 ) } )
		.end()
		.expectNet( "c" )
			.expectRegType()
			.expectArrayBounds( RANGE( 0, 10 ) )
		.end();
}

/***************************************************************************/

}