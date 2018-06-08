#include "stdafx.h"

#include "aep_test\fixtures\aep_test_checkers_fixture.hpp"

#include "aep_model\api\checkers\checker_values\aep_model_severity_level.hpp"

#include "common_tools\catch.hpp"

/***************************************************************************/

namespace AepTest {

/***************************************************************************/

namespace AEP = AepModel;

/***************************************************************************/

struct RangeBoundFixture 
	: public CheckersFixture
{

/***************************************************************************/

	RangeBoundFixture()
		:	CheckersFixture( Aep::CheckerIds::RangeBoundChecker )
		,	m_clk( "clk", AepModel::ClockEdge::Kind::OVL_POSEDGE )
		,	m_rst( "rst_n", AepModel::ResetPolarity::Kind::OVL_ACTIVE_HIGH )
	{

	}

/***************************************************************************/

	Aep::IAccessor::GlobalClockParameters m_clk;

	Aep::IAccessor::GlobalResetParameters m_rst;

/***************************************************************************/

};

/***************************************************************************/

TEST_CASE_METHOD( RangeBoundFixture, "simple id in range expression", "[range checker]" )
{
	const std::string code = 
		"module test ( input rst_n, clk, input [2:0] a, b, output reg c ); \n"
		"                                                                  \n"
		" always@( posedge clk )                                           \n"
		"  if( rst_n )                                                     \n"
		"   c = 0;                                                         \n"
		"  else                                                            \n"
		"   c = a[ b ];                                                    \n"
		"                                                                  \n"
		"endmodule                                                         \n"
		"                                                                  \n"
		"module testbench ();                                              \n"
		"                                                                  \n"
		" reg clk;                                                         \n"
		" reg [3:0] a, b;                                                  \n"
		" reg rst_n;                                                       \n"
		" wire c;                                                          \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  clk = 0;                                                        \n"
		"  rst_n = 1;                                                      \n"
		" forever                                                          \n"
		"  #10 clk = ~clk;                                                 \n"
		" end                                                              \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  rst_n = 0;                                                      \n"
		"  a = 1;                                                          \n"
		"  b = 0;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"  a = 4;                                                          \n"
		"  b = 2;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"   b = 3;                                                         \n"
		"                                                                  \n"
		"                                                                  \n"
		"  #50 $finish;                                                    \n"
		"                                                                  \n"
		" end                                                              \n"
		"                                                                  \n"
		" test dut( .a(a), .b(b), .clk(clk), .rst_n(rst_n), .c(c) );       \n"
		"                                                                  \n"
		"endmodule                                                         \n";

	run( code, m_clk, m_rst );

	expectContext( "test" )
		
		.instances()
			( "dut" )
		.end()
		
		.ports()
			( "b", "b", 3 )
			( "clk", "clk", 1 )
			( "rst_n", "rst_n", 1 )
		.end()
		
		.checker( 0 )
			.id( AepModel::OvlCheckerIds::Kind::OvlAlways )
			.instanceName( "check_overflow_1" )
			.suspectLine( 7 )

			.genericsParameters( 4 )
			.genericParameter< AEP::ClockEdge >( 
					AEP::GenericType::Kind::ClockEdge
				,	AEP::ClockEdge::Kind::OVL_POSEDGE 
			)
			.genericParameter< AEP::ResetPolarity >( 
					AEP::GenericType::Kind::ResetPolarity
				,	AEP::ResetPolarity::Kind::OVL_ACTIVE_HIGH
			)
			.genericParameter<  AEP::SeverityLevel > (
					AEP::GenericType::Kind::SeverityLevel
				,	AEP::SeverityLevel::Kind::OVL_ERROR 
			)
			.ports( 5 )
			.port( AepModel::OvlCheckerPortKind::Kind::Clock, "clk" )
			.port( AepModel::OvlCheckerPortKind::Kind::Reset, "rst_n" )
			.port( AepModel::OvlCheckerPortKind::Kind::TestExpression, "test_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Fire, "fire_range_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Enable, "1'b1" )
			
			.innerWires()
				( "test_overflow_1", "b < 3", 1 )
			.end()

		.end()
	;
}

/***************************************************************************/

TEST_CASE_METHOD( RangeBoundFixture, "logic expression in range expression_a", "[range checker]" )
{
	const std::string code = 
		"module test ( input rst_n, clk, input [2:0] a, b, output reg c ); \n"
		"                                                                  \n"
		" always@( posedge clk )                                           \n"
		"  if( rst_n )                                                     \n"
		"   c = 0;                                                         \n"
		"  else                                                            \n"
		"   c = a[ !b ];                                                   \n"
		"                                                                  \n"
		"endmodule                                                         \n"
		"                                                                  \n"
		"module testbench ();                                              \n"
		"                                                                  \n"
		" reg clk;                                                         \n"
		" reg [3:0] a, b;                                                  \n"
		" reg rst_n;                                                       \n"
		" wire c;                                                          \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  clk = 0;                                                        \n"
		"  rst_n = 1;                                                      \n"
		" forever                                                          \n"
		"  #10 clk = ~clk;                                                 \n"
		" end                                                              \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  rst_n = 0;                                                      \n"
		"  a = 1;                                                          \n"
		"  b = 0;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"  a = 4;                                                          \n"
		"  b = 2;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"   b = 3;                                                         \n"
		"                                                                  \n"
		"                                                                  \n"
		"  #50 $finish;                                                    \n"
		"                                                                  \n"
		" end                                                              \n"
		"                                                                  \n"
		" test dut( .a(a), .b(b), .clk(clk), .rst_n(rst_n), .c(c) );       \n"
		"                                                                  \n"
		"endmodule                                                         \n";

	run( code, m_clk, m_rst );

	expectContext( "test" )
		
		.instances()
			( "dut" )
		.end()
		
		.ports()
			( "b", "b", 3 )
			( "clk", "clk", 1 )
			( "rst_n", "rst_n", 1 )
		.end()
		
		.checker( 0 )
			.id( AepModel::OvlCheckerIds::Kind::OvlAlways )
			.instanceName( "check_overflow_1" )
			.suspectLine( 7 )

			.genericsParameters( 4 )
				.genericParameter< AEP::ClockEdge >( 
					AEP::GenericType::Kind::ClockEdge
				,	AEP::ClockEdge::Kind::OVL_POSEDGE 
			)
			.genericParameter< AEP::ResetPolarity >( 
					AEP::GenericType::Kind::ResetPolarity
				,	AEP::ResetPolarity::Kind::OVL_ACTIVE_HIGH
			)
			.genericParameter<  AEP::SeverityLevel > (
					AEP::GenericType::Kind::SeverityLevel
				,	AEP::SeverityLevel::Kind::OVL_ERROR 
			)

			.ports( 5 )
			.port( AepModel::OvlCheckerPortKind::Kind::Clock, "clk" )
			.port( AepModel::OvlCheckerPortKind::Kind::Reset, "rst_n" )
			.port( AepModel::OvlCheckerPortKind::Kind::TestExpression, "test_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Fire, "fire_range_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Enable, "1'b1" )
			
			.innerWires()
				( "test_overflow_1", "!b < 3", 1 )
			.end()

		.end()
	;
}

/***************************************************************************/

TEST_CASE_METHOD( RangeBoundFixture, "logic expression in range expression_b", "[range checker]" )
{
	const std::string code = 
		"module test ( input rst_n, clk, input [2:0] a, b, output reg c ); \n"
		"                                                                  \n"
		" always@( posedge clk )                                           \n"
		"  if( rst_n )                                                     \n"
		"   c = 0;                                                         \n"
		"  else                                                            \n"
		"   c = a[ b ^ 1'b0 ];                                             \n"
		"                                                                  \n"
		"endmodule                                                         \n"
		"                                                                  \n"
		"module testbench ();                                              \n"
		"                                                                  \n"
		" reg clk;                                                         \n"
		" reg [3:0] a, b;                                                  \n"
		" reg rst_n;                                                       \n"
		" wire c;                                                          \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  clk = 0;                                                        \n"
		"  rst_n = 1;                                                      \n"
		" forever                                                          \n"
		"  #10 clk = ~clk;                                                 \n"
		" end                                                              \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  rst_n = 0;                                                      \n"
		"  a = 1;                                                          \n"
		"  b = 0;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"  a = 4;                                                          \n"
		"  b = 2;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"   b = 3;                                                         \n"
		"                                                                  \n"
		"                                                                  \n"
		"  #50 $finish;                                                    \n"
		"                                                                  \n"
		" end                                                              \n"
		"                                                                  \n"
		" test dut( .a(a), .b(b), .clk(clk), .rst_n(rst_n), .c(c) );       \n"
		"                                                                  \n"
		"endmodule                                                         \n";

	run( code, m_clk, m_rst );

	expectContext( "test" )
		
		.instances()
			( "dut" )
		.end()
		
		.ports()
			( "b", "b", 3 )
			( "clk", "clk", 1 )
			( "rst_n", "rst_n", 1 )
		.end()
		
		.checker( 0 )
			.id( AepModel::OvlCheckerIds::Kind::OvlAlways )
			.instanceName( "check_overflow_1" )
			.suspectLine( 7 )

			.genericsParameters( 4 )
			.genericParameter< AEP::ClockEdge >( 
					AEP::GenericType::Kind::ClockEdge
				,	AEP::ClockEdge::Kind::OVL_POSEDGE 
			)
			.genericParameter< AEP::ResetPolarity >( 
					AEP::GenericType::Kind::ResetPolarity
				,	AEP::ResetPolarity::Kind::OVL_ACTIVE_HIGH
			)
			.genericParameter<  AEP::SeverityLevel > (
					AEP::GenericType::Kind::SeverityLevel
				,	AEP::SeverityLevel::Kind::OVL_ERROR 
			)

			.ports( 5 )
			.port( AepModel::OvlCheckerPortKind::Kind::Clock, "clk" )
			.port( AepModel::OvlCheckerPortKind::Kind::Reset, "rst_n" )
			.port( AepModel::OvlCheckerPortKind::Kind::TestExpression, "test_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Fire, "fire_range_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Enable, "1'b1" )
			
			.innerWires()
				( "test_overflow_1", "( b ^ 1'b0 ) < 3", 1 )
			.end()

		.end()
	;
}

/***************************************************************************/

TEST_CASE_METHOD( RangeBoundFixture, "arith expression in range expression", "[range checker]" )
{
	const std::string code = 
		"module test ( input rst_n, clk, input [2:0] a, b, output reg c ); \n"
		"                                                                  \n"
		" always@( posedge clk )                                           \n"
		"  if( rst_n )                                                     \n"
		"   c = 0;                                                         \n"
		"  else                                                            \n"
		"   c = a[ b + c ];                                                \n"
		"                                                                  \n"
		"endmodule                                                         \n"
		"                                                                  \n"
		"module testbench ();                                              \n"
		"                                                                  \n"
		" reg clk;                                                         \n"
		" reg [3:0] a, b;                                                  \n"
		" reg rst_n;                                                       \n"
		" wire c;                                                          \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  clk = 0;                                                        \n"
		"  rst_n = 1;                                                      \n"
		" forever                                                          \n"
		"  #10 clk = ~clk;                                                 \n"
		" end                                                              \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  rst_n = 0;                                                      \n"
		"  a = 1;                                                          \n"
		"  b = 0;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"  a = 4;                                                          \n"
		"  b = 2;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"   b = 3;                                                         \n"
		"                                                                  \n"
		"                                                                  \n"
		"  #50 $finish;                                                    \n"
		"                                                                  \n"
		" end                                                              \n"
		"                                                                  \n"
		" test dut( .a(a), .b(b), .clk(clk), .rst_n(rst_n), .c(c) );       \n"
		"                                                                  \n"
		"endmodule                                                         \n";

	run( code, m_clk, m_rst );

	expectContext( "test" )
		
		.instances()
			( "dut" )
		.end()
		
		.ports()
			( "b", "b", 3 )
			( "c", "c", 1 )
			( "clk", "clk", 1 )
			( "rst_n", "rst_n", 1 )
		.end()
		
		.checker( 0 )
			.id( AepModel::OvlCheckerIds::Kind::OvlAlways )
			.instanceName( "check_overflow_1" )
			.suspectLine( 7 )

			.genericsParameters( 4 )
				.genericParameter< AEP::ClockEdge >( 
					AEP::GenericType::Kind::ClockEdge
				,	AEP::ClockEdge::Kind::OVL_POSEDGE 
			)
			.genericParameter< AEP::ResetPolarity >( 
					AEP::GenericType::Kind::ResetPolarity
				,	AEP::ResetPolarity::Kind::OVL_ACTIVE_HIGH
			)
			.genericParameter<  AEP::SeverityLevel > (
					AEP::GenericType::Kind::SeverityLevel
				,	AEP::SeverityLevel::Kind::OVL_ERROR 
			)

			.ports( 5 )
			.port( AepModel::OvlCheckerPortKind::Kind::Clock, "clk" )
			.port( AepModel::OvlCheckerPortKind::Kind::Reset, "rst_n" )
			.port( AepModel::OvlCheckerPortKind::Kind::TestExpression, "test_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Fire, "fire_range_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Enable, "1'b1" )
			
			.innerWires()
				( "test_overflow_1", "( b + c ) < 3", 1 )
			.end()

		.end()
	;
}

/***************************************************************************/

TEST_CASE_METHOD( RangeBoundFixture, "no reset", "[range checker]" )
{
	const std::string code = 
		"module test ( input clk, input [2:0] a, b, output reg c ); \n"
		"                                                                  \n"
		" always@( posedge clk )                                           \n"
		"   c = a[ b + c ];                                                \n"
		"                                                                  \n"
		"endmodule                                                         \n"
		"                                                                  \n"
		"module testbench ();                                              \n"
		"                                                                  \n"
		" reg clk;                                                         \n"
		" reg [3:0] a, b;                                                  \n"
		" reg rst_n;                                                       \n"
		" wire c;                                                          \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  clk = 0;                                                        \n"
		"  rst_n = 1;                                                      \n"
		" forever                                                          \n"
		"  #10 clk = ~clk;                                                 \n"
		" end                                                              \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  rst_n = 0;                                                      \n"
		"  a = 1;                                                          \n"
		"  b = 0;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"  a = 4;                                                          \n"
		"  b = 2;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"   b = 3;                                                         \n"
		"                                                                  \n"
		"                                                                  \n"
		"  #50 $finish;                                                    \n"
		"                                                                  \n"
		" end                                                              \n"
		"                                                                  \n"
		" test dut( .a(a), .b(b), .clk(clk), .c(c) );                      \n"
		"                                                                  \n"
		"endmodule                                                         \n";

	run( code, m_clk );

	expectContext( "test" )
		
		.instances()
			( "dut" )
		.end()
		
		.ports()
			( "b", "b", 3 )
			( "c", "c", 1 )
			( "clk", "clk", 1 )
		.end()
		
		.checker( 0 )
			.id( AepModel::OvlCheckerIds::Kind::OvlAlways )
			.instanceName( "check_overflow_1" )
			.suspectLine( 4 )

			.genericsParameters( 4 )
			.genericParameter< AEP::ClockEdge >( 
					AEP::GenericType::Kind::ClockEdge
				,	AEP::ClockEdge::Kind::OVL_POSEDGE 
			)
			.genericParameter< AEP::ResetPolarity >( 
					AEP::GenericType::Kind::ResetPolarity
				,	AEP::ResetPolarity::Kind::OVL_ACTIVE_LOW
			)
			.genericParameter<  AEP::SeverityLevel > (
					AEP::GenericType::Kind::SeverityLevel
				,	AEP::SeverityLevel::Kind::OVL_ERROR 
			)

			.ports( 5 )
			.port( AepModel::OvlCheckerPortKind::Kind::Clock, "clk" )
			.port( AepModel::OvlCheckerPortKind::Kind::Reset, "1'b1" )
			.port( AepModel::OvlCheckerPortKind::Kind::TestExpression, "test_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Fire, "fire_range_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Enable, "1'b1" )
			
			.innerWires()
				( "test_overflow_1", "( b + c ) < 3", 1 )
			.end()

		.end()
	;
}

/***************************************************************************/

TEST_CASE_METHOD( RangeBoundFixture, "couple instances", "[range checker]" )
{
	const std::string code = 
		"module test ( input rst_n, clk, input [2:0] a, b, output reg c ); \n"
		"                                                                  \n"
		" always@( posedge clk )                                           \n"
		"  if( rst_n )                                                     \n"
		"   c = 0;                                                         \n"
		"  else                                                            \n"
		"   c = a[ b + c ];                                                \n"
		"                                                                  \n"
		"endmodule                                                         \n"
		"                                                                  \n"
		"module testbench ();                                              \n"
		"                                                                  \n"
		" reg clk;                                                         \n"
		" reg [3:0] a, b;                                                  \n"
		" reg rst_n;                                                       \n"
		" wire c[1:0];                                                     \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  clk = 0;                                                        \n"
		"  rst_n = 1;                                                      \n"
		" forever                                                          \n"
		"  #10 clk = ~clk;                                                 \n"
		" end                                                              \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  rst_n = 0;                                                      \n"
		"  a = 1;                                                          \n"
		"  b = 0;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"  a = 4;                                                          \n"
		"  b = 2;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"   b = 3;                                                         \n"
		"                                                                  \n"
		"                                                                  \n"
		"  #50 $finish;                                                    \n"
		"                                                                  \n"
		" end                                                              \n"
		"                                                                  \n"
		" test dut1( .a(a), .b(b), .clk(clk), .rst_n(rst_n), .c(c[0]) );   \n"
		" test dut2( .a(b), .b(a), .clk(!clk), .rst_n(!rst_n), .c(c[1]) ); \n"
		"                                                                  \n"
		"endmodule                                                         \n";

	run( code, m_clk, m_rst );

	expectContext( "test" )
		
		.instances()
			( "dut1" )
			( "dut2" )
		.end()
		
		.ports()
			( "b", "b", 3 )
			( "c", "c", 1 )
			( "clk", "clk", 1 )
			( "rst_n", "rst_n", 1 )
		.end()
		
		.checker( 0 )
			.id( AepModel::OvlCheckerIds::Kind::OvlAlways )
			.instanceName( "check_overflow_1" )
			.suspectLine( 7 )

			.genericsParameters( 4 )
				.genericParameter< AEP::ClockEdge >( 
					AEP::GenericType::Kind::ClockEdge
				,	AEP::ClockEdge::Kind::OVL_POSEDGE 
			)
			.genericParameter< AEP::ResetPolarity >( 
					AEP::GenericType::Kind::ResetPolarity
				,	AEP::ResetPolarity::Kind::OVL_ACTIVE_HIGH
			)
			.genericParameter<  AEP::SeverityLevel > (
					AEP::GenericType::Kind::SeverityLevel
				,	AEP::SeverityLevel::Kind::OVL_ERROR 
			)

			.ports( 5 )
			.port( AepModel::OvlCheckerPortKind::Kind::Clock, "clk" )
			.port( AepModel::OvlCheckerPortKind::Kind::Reset, "rst_n" )
			.port( AepModel::OvlCheckerPortKind::Kind::TestExpression, "test_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Fire, "fire_range_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Enable, "1'b1" )
			
			.innerWires()
				( "test_overflow_1", "( b + c ) < 3", 1 )
			.end()

		.end()
	;
}

/***************************************************************************/

TEST_CASE_METHOD( RangeBoundFixture, "suspect in if", "[range checker]" )
{
	const std::string code = 
		"module test ( input rst_n, clk, input [2:0] a, b, output reg c ); \n"
		"                                                                  \n"
		" always@( posedge clk )                                           \n"
		"  if( rst_n )                                                     \n"
		"   c = 0;                                                         \n"
		"  else if( b < 3 )                                                \n"
		"   c = a[ b ];                                                    \n"
		"                                                                  \n"
		"endmodule                                                         \n"
		"                                                                  \n"
		"module testbench ();                                              \n"
		"                                                                  \n"
		" reg clk;                                                         \n"
		" reg [3:0] a, b;                                                  \n"
		" reg rst_n;                                                       \n"
		" wire c[1:0];                                                     \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  clk = 0;                                                        \n"
		"  rst_n = 1;                                                      \n"
		" forever                                                          \n"
		"  #10 clk = ~clk;                                                 \n"
		" end                                                              \n"
		"                                                                  \n"
		" initial begin                                                    \n"
		"  rst_n = 0;                                                      \n"
		"  a = 1;                                                          \n"
		"  b = 0;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"  a = 4;                                                          \n"
		"  b = 2;                                                          \n"
		"                                                                  \n"
		"  #50                                                             \n"
		"   b = 3;                                                         \n"
		"                                                                  \n"
		"                                                                  \n"
		"  #50 $finish;                                                    \n"
		"                                                                  \n"
		" end                                                              \n"
		"                                                                  \n"
		" test dut1( .a(a), .b(b), .clk(clk), .rst_n(rst_n), .c(c[0]) );   \n"
		" test dut2( .a(b), .b(a), .clk(!clk), .rst_n(!rst_n), .c(c[1]) ); \n"
		"                                                                  \n"
		"endmodule                                                         \n";

	run( code, m_clk, m_rst );

	expectContext( "test" )
		
		.instances()
			( "dut1" )
			( "dut2" )
		.end()
		
		.ports()
			( "b", "b", 3 )
			( "clk", "clk", 1 )
			( "rst_n", "rst_n", 1 )
		.end()
		
		.checker( 0 )
			.id( AepModel::OvlCheckerIds::Kind::OvlAlways )
			.instanceName( "check_overflow_1" )
			.suspectLine( 7 )

			.genericsParameters( 4 )
				.genericParameter< AEP::ClockEdge >( 
					AEP::GenericType::Kind::ClockEdge
				,	AEP::ClockEdge::Kind::OVL_POSEDGE 
			)
			.genericParameter< AEP::ResetPolarity >( 
					AEP::GenericType::Kind::ResetPolarity
				,	AEP::ResetPolarity::Kind::OVL_ACTIVE_HIGH
			)
			.genericParameter<  AEP::SeverityLevel > (
					AEP::GenericType::Kind::SeverityLevel
				,	AEP::SeverityLevel::Kind::OVL_ERROR 
			)

			.ports( 5 )
			.port( AepModel::OvlCheckerPortKind::Kind::Clock, "clk" )
			.port( AepModel::OvlCheckerPortKind::Kind::Reset, "rst_n" )
			.port( AepModel::OvlCheckerPortKind::Kind::TestExpression, "test_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Fire, "fire_range_overflow_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Enable, "1'b1" )
			
			.innerWires()
				( "test_overflow_1", "b < 3", 1 )
			.end()

		.end()
	;
}

/***************************************************************************/

}

/***************************************************************************/