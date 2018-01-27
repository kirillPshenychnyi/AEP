#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_ports_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "simple input port", "[ports]" )
{
	std::string code =
		"module top (input a);	\n"
		"	NOT u1 (a);			\n"
		"endmodule				\n"
		;

	runImport( code );

	expectUnit( "top" )
		.expectPort( "a" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "couple input ports", "[ports]" )
{
	std::string code =
		"module unit (input a, b, c);	\n"
		"	NOT u1 (a);					\n"
		"endmodule						\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end()
		.expectPort( "b" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end()
		.expectPort( "c" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "couple input ports explicit wire", "[ports]" )
{
	std::string code =
		"module unit (input wire a, b, c);	\n"
		"	NOT u1 (a);						\n"
		"endmodule							\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end()
		.expectPort( "b" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end()
		.expectPort( "c" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "couple input declarations", "[ports]" )
{
	std::string code =
		"module unit (input a, input b, input c);	\n"
		"	NOT u1 (a);								\n"
		"endmodule									\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end()
		.expectPort( "b" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end()
		.expectPort( "c" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "two bit input", "[ports]" )
{
	std::string code =
		"module unit (input [1:0] a);		\n"
		"	NOT u1 (a);						\n"
		"endmodule							\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
			.expectBounds( "1", "0" )
		.end();
}

TEST_CASE_METHOD( PortsFixture, "two bit input reverse bit order", "[ports]" )
{
	std::string code =
		"module unit (input [0:1] a);		\n"
		"	NOT u1 (a);						\n"
		"endmodule							\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
			.expectBounds( "0", "1" )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "couple multibit inputs", "[ports]" )
{
	std::string code =
		"module unit (input [1:0] a, b, c);		\n"
		"	NOT u1 (a);							\n"
		"endmodule								\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
			.expectBounds( "1", "0" )
		.end()
		.expectPort( "b" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
			.expectBounds( "1", "0" )
		.end()
		.expectPort( "c" )
			.expectDirection( VlogDM::PortDirection::Direction::Input )
			.expectNetType( VlogDM::NetKind::Kind::wire )
			.expectBounds( "1", "0" )
		.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "couple different multibit inputs", "[ports]" )
{
	std::string code =
		"module unit (input [1:0] a, input [3:0] b );		\n"
		"	NOT u1 (a);										\n"
		"endmodule											\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
	.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "1", "0" )
	.end()
	.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "3", "0" )
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "couple different multibit inputs big little endian", "[ports]" )
{
	std::string code =
		"module unit (input [1:0] a, input [0:3] b );		\n"
		"	NOT u1 (a);										\n"
		"endmodule											\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
	.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "1", "0" )
	.end()
	.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "0", "3" )
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "simple output", "[ports]" )
{
	std::string code =
		"module unit (output a);		\n"
		"	NOT u1 (a);					\n"
		"endmodule						\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectNetType( VlogDM::NetKind::Kind::wire )
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "simple reg output", "[ports]" )
{
	std::string code =
		"module unit (output reg a);	\n"
		"	NOT u1 (a);					\n"
		"endmodule						\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "couple reg outputs", "[ports]" )
{
	std::string code =
		"module unit (output reg a, b, c );		\n"
		"	NOT u1 (a);							\n"
		"endmodule								\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
	.end()
		.expectPort( "c" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "different outputs", "[ports]" )
{
	std::string code =
		"module unit (output reg a, output b, output reg c );	\n"
		"	NOT u1 (a);											\n"
		"endmodule												\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectNetType( VlogDM::NetKind::Kind::wire )
	.end()
		.expectPort( "c" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "simple module interface", "[ports]" )
{
	std::string code =
		"module unit (input a, output reg b);		\n"
		"	NOT u1 (a);								\n"
		"endmodule									\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "multibit module interface", "[ports]" )
{
	std::string code =
		"module unit (input [7:0] a, output reg [7:0] b);	\n"
		"	NOT u1 (a);										\n"
		"endmodule											\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "7", "0" )
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
		.expectBounds( "7", "0" )
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "different modules same interface", "[ports]" )
{
	std::string code =
		"module unit (input [7:0] a, output reg [7:0] b);	\n"
		"	NOT u1 (a);										\n"
		"endmodule											\n"
		"													\n"
		"module top (input [7:0] a, output reg [7:0] b);	\n"
		"	NOT u1 (a);										\n"
		"endmodule											\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "7", "0" )
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
		.expectBounds( "7", "0" )
	.end();

	expectUnit( "top" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "7", "0" )
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
		.expectBounds( "7", "0" )
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "non-ansi input port declaration", "[ports]" )
{
	std::string code =
		"module unit (a,b);					\n"
		"	input a,b;						\n"
		"endmodule							\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "non-ansi interface", "[ports]" )
{
	std::string code =
		"module unit (a,b);					\n"
		"	input a;						\n"
		"	output b;						\n"
		"endmodule							\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectNetType( VlogDM::NetKind::Kind::wire )
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "non-ansi multibit interface", "[ports]" )
{
	std::string code =
		"module unit (a,b);					\n"
		"	input [3:0] a;					\n"
		"	output reg [7:0] b;				\n"
		"endmodule							\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "3", "0" )
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
		.expectBounds( "7", "0" )
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "non-ansi multibit interface couple ports", "[ports]" )
{
	std::string code =
		"module unit (a,b);					\n"
		"	input [3:0] a, b;				\n"
		"	output reg [7:0] c, d;			\n"
		"endmodule							\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( "a" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "3", "0" )
	.end()
		.expectPort( "b" )
		.expectDirection( VlogDM::PortDirection::Direction::Input )
		.expectNetType( VlogDM::NetKind::Kind::wire )
		.expectBounds( "3", "0" )
	.end()
	.expectPort( "c" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
		.expectBounds( "7", "0" )
	.end()
	.expectPort( "d" )
		.expectDirection( VlogDM::PortDirection::Direction::Output )
		.expectRegType()
		.expectBounds( "7", "0" )
	.end();
}

/***************************************************************************/

}