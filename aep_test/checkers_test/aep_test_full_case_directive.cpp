#include "stdafx.h"

#include "aep_test\fixtures\aep_test_checkers_fixture.hpp"

#include "aep_model\api\checkers\checker_values\aep_model_severity_level.hpp"

#include "common_tools\catch.hpp"

/***************************************************************************/

namespace AepTest {

/***************************************************************************/

namespace AEP = AepModel;

/***************************************************************************/

struct ParallelCaseFixture 
	: public CheckersFixture
{

/***************************************************************************/

	ParallelCaseFixture()
		:	CheckersFixture( Aep::CheckerIds::ParallelCaseSynDirectiveChecker )
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

TEST_CASE_METHOD( ParallelCaseFixture, "suspect within comb process", "[parallel_case directive checker]" )
{
	const std::string code = 
		"module test ( input rst_n, clk, a, output reg y );       \n"
		"                                                         \n"
		"  reg [2:0] sel;                                         \n"
		"                                                         \n"
		"  always@( posedge clk )                                 \n"
		"     if( rst_n )                                         \n"
		"        sel = 0;                                         \n"
		"     else                                                \n"
		"        sel = sel + 1;                                   \n"
		"														  \n"
		"     always @ ( * )                                      \n"
		"      (* parallel_case *) casex ( sel )                  \n"
		"         3'b1xx: y = 0;                                  \n"
		"         3'bx10: y = 1;                                  \n"
		"         3'bxx1: y = a;                                  \n"
		"      endcase                                            \n"
		"                                                         \n"
		"endmodule                                                \n"
		"                                                         \n"
		"module top( input rst, clk, a, y );                      \n"
		"														  \n"
		"  test dut( rst, clk, a, y );                            \n"
		"  test dut1( rst, clk, !a, y );                          \n"
		"                                                         \n"
		"endmodule                                                \n";

	run( code, m_clk, m_rst );

	contextsCount( 1 );

	expectContext( "test" )
		
		.instances()
			( "dut" )
			( "dut1" )
		.end()
		
		.ports()
			( "sel", "sel", 3 )
			( "clk", "clk", 1 )
			( "rst_n", "rst_n", 1 )
		.end()
		
		.checker( 0 )
			.id( AepModel::OvlCheckerIds::Kind::OvlOneHot )
			.instanceName( "check_parallel_case_1" )
			.suspectLine( 12 )

			.genericsParameters( 5 )
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
			.genericParameter< int > ( AEP::GenericType::Kind::Width, 3 )
			.ports( 5 )
			.port( AepModel::OvlCheckerPortKind::Kind::Clock, "clk" )
			.port( AepModel::OvlCheckerPortKind::Kind::Reset, "rst_n" )
			.port( AepModel::OvlCheckerPortKind::Kind::TestExpression, "test_parallel_case_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Fire, "fire_parallel_case_1" )
			.port( AepModel::OvlCheckerPortKind::Kind::Enable, "1'b1" )
			
			.innerWires()
				( 
					"test_parallel_case_1"
				,	"{( case_sel_wire_line_12 == 3'b1xx ) !== 1'b0"
					", ( case_sel_wire_line_12 == 3'bx10 ) !== 1'b0"
					", ( case_sel_wire_line_12 == 3'bxx1 ) !== 1'b0}"
				,	3
				)
			( "case_sel_wire_line_12", "sel", 3 )
			.end()

		.end()
	;
}

/***************************************************************************/

}