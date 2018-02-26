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

TEST_CASE_METHOD( ProcessFixture, "constant slice select", "[dataflow]" )
{
	std::string code =
		"module top (input [4:0] b, output [2:0] c);	\n"
		"	assign c = b[ 2 : 0 ];						\n"
		"endmodule										\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "multidimensional sel expression", "[dataflow]" )
{
	std::string code =
		"module top (input sel, offset, output out );	\n"
		"	reg [3:0] mem [7:0]	;						\n"
		"	assign out = mem[ sel ][ offset ];			\n"
		"endmodule										\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 3, 3 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "assign to output bit", "[dataflow]" )
{
	std::string code =
		"module top (input sel, offset, output [3:0] out );	\n"
		"	reg [3:0] mem [7:0]	;							\n"
		"	assign out[ 0 ] = mem[ sel ][ offset ];			\n"
		"endmodule											\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 3, 3 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "assign to output slice", "[dataflow]" )
{
	std::string code =
		"module top (input sel, offset, output [3:0] out );	\n"
		"	reg [3:0] mem [7:0]	;							\n"
		"	assign out[ 2 : 0 ] = mem[ sel ][ 3 : 1 ];		\n"
		"endmodule											\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 3, 3 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "array assigns", "[dataflow]" )
{
	std::string code =
		"module top (input sel, offset );							\n"
		"	reg [3:0] mem [7:0]	;									\n"
		"	wire [3:0] target [3:0];								\n"
		"	assign target[ sel ][ offset ] = mem[ sel ][ offset ];	\n"
		"endmodule													\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 4, 4 ) );
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

TEST_CASE_METHOD( ProcessFixture, "assign concat to nested concat", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c, d );			\n"
		"	assign { c, d } = { { a }, b };				\n"
		"endmodule										\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "assign multiconcat to output", "[dataflow]" )
{
	std::string code =
		"module top (input a, output b );	    \n"
		"	assign b = { 2{ a } };				\n"
		"endmodule								\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "assign multiconcat with nested expressions to output", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, c, d, output [5:0] e );	\n"
		"	assign b = { 2{ ( a | c ), d, c } };			\n"
		"endmodule											\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "multiconcat in concat", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, c, d, output [5:0] e );	\n"
		"	assign b = { a, b, { 2{ c, d } } };				\n"
		"endmodule											\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "concat of different literals", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, c, d, output [5:0] e );	\n"
		"	assign b = { 1'bx, 1'o0, 1'h1 };				\n"
		"endmodule											\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "mux via ternary", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, sel, output c);	\n"
		"	assign a = sel ? a : b;					\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "true branch as ternary", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, sel, output c);	\n"
		"	assign a = sel ? a ? 0 : 1 : b;			\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "both branches as ternary", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, sel, output c);	\n"
		"	assign a = sel ? a ? 0 : 1 : b ? 1 : 0;	\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 1 )
		.expectProcess( 0, LINES( 2, 2 ) );
}

/***************************************************************************/

TEST_CASE_METHOD( ProcessFixture, "couple dataflow processes", "[dataflow]" )
{
	std::string code =
		"module top (input a, b, output c, d);		\n"
		"	assign c = !a;							\n"
		"	assign d = ( a ^ b );					\n"
		"endmodule									\n"
		;

	runImport( code );

	expectDesignUnit( "top", 2 )
		.expectProcess( 0, LINES( 2, 2 ) )
		.expectProcess( 1, LINES( 3, 3 ) );
}

/***************************************************************************/

}