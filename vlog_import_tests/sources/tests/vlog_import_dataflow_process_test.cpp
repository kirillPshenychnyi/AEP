#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_process_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple signal assignment", "[dataflow]" )
{
	std::string code =
		"module top (input a, output b );	\n"
		"	assign a = b;					\n"
		"endmodule							\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple binary operator assignment", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c);	\n"
		"	assign c = ( a || b );			\n"
		"endmodule							\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "some boolean function", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, c, d, output e);	\n"
		"	assign e = ( ( a || b ) ^ ( c & d ) );	\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "boolean function with three operands", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c);			\n"
		"	assign c = ( ( a || b ) ^ c );			\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "complex boolean expression", "[dataflow]" )
{
	std::string code =
		"module top (input [1:0] a, b, c, d, output e);							\n"
		"	assign c = ( ( ( a[ 0 ] || b[ 1 ] ) ^ ( c[ 1 ] && d[ 0 ] ) ) || ( a[ 1 ] && d[ 0 ] ) );	\n"
		"endmodule																\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "binary operator negation", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c );	\n"
		"	assign c = !( b || a );				\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "binary operator with operand negation", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c );	\n"
		"	assign c = ( !b || a );				\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "binary operator with right operand negation", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c );	\n"
		"	assign c = ( b || !a );				\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "binary operator with both operand negation", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c );	\n"
		"	assign c = ( !b || !a );			\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "unary operator with both operand negation", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c );	\n"
		"	assign c = &( !b || !a );			\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "binary operator with unary expression operands", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, c, d, output e );		\n"
		"	assign e = ( !( a | b ) && !( c & d ) );	\n"
		"endmodule										\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "reduction xor", "[dataflow]" )
{
	std::string code =
		"module top (input [2:0] a, output c );	\n"
		"	assign c = ~^a;						\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "arithmetic expression", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c );	\n"
		"	assign c = ( a + b );				\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "arithmetic expression with unary minus", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c );	\n"
		"	assign c = ( a + -b );				\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "simple bit assignment", "[dataflow]" )
{
	std::string code =
		"module top (input [3:0] a, output c);	\n"
		"	assign c = a[ 0 ];					\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "port as bit select", "[dataflow]" )
{
	std::string code =
		"module top (input a, input [1:0] b, output c);	\n"
		"	assign c = b[ a ];							\n"
		"endmodule										\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "assign concat to output", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output [1:0] c);		\n"
		"	assign c = { a, b };						\n"
		"endmodule										\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "assign expressions concat to output", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, c, d, output [1:0] e);		\n"
		"	assign e = { ( a | b ), ( c | d ) };			\n"
		"endmodule											\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "assign concat to concat", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c, d );			\n"
		"	assign { c, d } = { a, b };					\n"
		"endmodule										\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

}