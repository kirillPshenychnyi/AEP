#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_expression_bitwidth_engine_fixture.hpp"

#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"

#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"
#include "vlog_data_model\api\vlog_dm_statement.hpp"
#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "scalar to scalar", "[bitwidth]" )
{
	std::string code =
		"module top (input a, output b );	\n"
		"	assign a = b;					\n"
		"endmodule							\n"
		;

	runImport( code );

	VlogDM::ContinuousAssignment const & assign = getContiniousAssignment( "top", 0 );

	expectBitwidth( assign.getAssignment().getRightOperand(), 1 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 1 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "vector to vector", "[bitwidth]" )
{
	std::string code =
		"module top (input [2:0] a, output [2:0] b );	\n"
		"	assign a = b;								\n"
		"endmodule										\n"
		;

	runImport( code );

	VlogDM::ContinuousAssignment const & assign = getContiniousAssignment( "top", 0 );

	expectBitwidth( assign.getAssignment().getRightOperand(), 3 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 3 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "array to array", "[bitwidth]" )
{
	std::string code =
		"module top ();									\n"
		"	reg a[2:0];									\n"
		"	reg b[2:0];									\n"
		"												\n"
		"	always@(*)									\n"
		"		a = b;									\n"
		"endmodule										\n"
		;

	runImport( code );

	VlogDM::BlockingAssignment const & assign = getBlockingAssign( "top", 0 );
	
	expectBitwidth( assign.getAssignment().getRightOperand(), 3 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 3 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "array sel to scalar", "[bitwidth]" )
{
	std::string code =
		"module top ();									\n"
		"	reg a;										\n"
		"	reg b[2:0];									\n"
		"												\n"
		"	always@(*)									\n"
		"		a = b[0];								\n"
		"endmodule										\n"
		;

	runImport( code );

	VlogDM::BlockingAssignment const & assign = getBlockingAssign( "top", 0 );
	
	expectBitwidth( assign.getAssignment().getRightOperand(), 1 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 1 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "array sel to vector", "[bitwidth]" )
{
	std::string code =
		"module top ();									\n"
		"	reg [2:0] a;								\n"
		"	reg b[4:0];									\n"
		"												\n"
		"	always@(*)									\n"
		"		a = b[1:3];								\n"
		"endmodule										\n"
		;

	runImport( code );

	VlogDM::BlockingAssignment const & assign = getBlockingAssign( "top", 0 );
	
	expectBitwidth( assign.getAssignment().getRightOperand(), 3 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 3 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "arith exression to scalar", "[bitwidth]" )
{
	std::string code =
		"module top ();									\n"
		"	reg [2:0] a;								\n"
		"	reg b[2:0], c[2:0];							\n"
		"												\n"
		"	always@(*)									\n"
		"		a = c + b;								\n"
		"endmodule										\n"
		;

	runImport( code );

	VlogDM::BlockingAssignment const & assign = getBlockingAssign( "top", 0 );
	
	expectBitwidth( assign.getAssignment().getRightOperand(), 3 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 3 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "binary expression with different operands", "[bitwidth]" )
{
	std::string code =
		"module top (input [1:0] a, input [3:0] c, output [3:0] b );	\n"
		"	assign b = a + c;											\n"
		"endmodule														\n"
		;

	runImport( code );

	VlogDM::ContinuousAssignment const & assign = getContiniousAssignment( "top", 0 );

	expectBitwidth( assign.getAssignment().getRightOperand(), 4 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 4 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "expression with different width operands", "[bitwidth]" )
{
	std::string code =
		"module top (input [1:0] a, input [2:0] b, input [3:0] c, output d );	\n"
		"	assign d = a + b * c;												\n"
		"endmodule																\n"
		;

	runImport( code );

	VlogDM::ContinuousAssignment const & assign = getContiniousAssignment( "top", 0 );

	expectBitwidth( assign.getAssignment().getRightOperand(), 4 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 1 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "logic bitwise expression", "[bitwidth]" )
{
	std::string code =
		"module top (input [1:0] a, input [2:0] b, input [3:0] c, output d );	\n"
		"	assign d = a | b ^ c;												\n"
		"endmodule																\n"
		;

	runImport( code );

	VlogDM::ContinuousAssignment const & assign = getContiniousAssignment( "top", 0 );

	expectBitwidth( assign.getAssignment().getRightOperand(), 4 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 1 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "logic expression", "[bitwidth]" )
{
	std::string code =
		"module top (input [1:0] a, input [2:0] b, input [3:0] c, output d );	\n"
		"	assign d = ( a == b ) | ( a === b );								\n"
		"endmodule																\n"
		;

	runImport( code );

	VlogDM::ContinuousAssignment const & assign = getContiniousAssignment( "top", 0 );

	expectBitwidth( assign.getAssignment().getRightOperand(), 1 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 1 );
}

/***************************************************************************/

TEST_CASE_METHOD( ExpressionBitwidthEngineFixture, "conditional expression", "[bitwidth]" )
{
	std::string code =
		"module top (input [1:0] a, input b, input [1:0] c, output [1:0] d );	\n"
		"	assign d = ( a == 2'b00 ) ? c : b;									\n"
		"endmodule																\n"
		;

	runImport( code );

	VlogDM::ContinuousAssignment const & assign = getContiniousAssignment( "top", 0 );

	expectBitwidth( assign.getAssignment().getRightOperand(), 2 );
	expectBitwidth( assign.getAssignment().getLeftOperand(), 2 );
}

/***************************************************************************/

}

/***************************************************************************/
