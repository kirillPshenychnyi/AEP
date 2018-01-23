#include "stdafx.h"

#include "vlog_import_tests\catch.hpp"
#include "vlog_import_tests\sources\fixtures\vlog_import_ports_fixture.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

#define PORT_INFO( _name, _bounds, _direction, _netType )		\
	std::make_tuple(											\
			_name												\
		,	_bounds												\
		,	VlogDM::PortDirection::Direction::_direction		\
		,	VlogDM::NetType::Type::_netType						\
	)

#define RANGE( _rightBound, _leftBound )						\
	std::make_pair( #_rightBound, #_leftBound  )

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
		.expectPort( PORT_INFO( "a", boost::none, Input, wire ) )
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
		.expectPort( PORT_INFO( "a", boost::none, Input, wire ) )
		.expectPort( PORT_INFO( "b", boost::none, Input, wire ) )
		.expectPort( PORT_INFO( "c", boost::none, Input, wire ) )
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
		.expectPort( PORT_INFO( "a", boost::none, Input, wire ) )
		.expectPort( PORT_INFO( "b", boost::none, Input, wire ) )
		.expectPort( PORT_INFO( "c", boost::none, Input, wire ) )
	.end();
}

/***************************************************************************/

TEST_CASE_METHOD( PortsFixture, "explicit input wire ports", "[ports]" )
{
	std::string code =
		"module unit (input wire a, b, c);	\n"
		"	NOT u1 (a);						\n"
		"endmodule							\n"
		;

	runImport( code );
	
	expectUnit( "unit" )
		.expectPort( PORT_INFO( "a", boost::none, Input, wire ) )
		.expectPort( PORT_INFO( "b", boost::none, Input, wire ) )
		.expectPort( PORT_INFO( "c", boost::none, Input, wire ) )
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
		.expectPort( PORT_INFO( "a", boost::none, Input, wire ) )
		.expectPort( PORT_INFO( "b", boost::none, Input, wire ) )
		.expectPort( PORT_INFO( "c", boost::none, Input, wire ) )
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
		.expectPort( PORT_INFO( "a", Bounds( "1", "0" ), Input, wire ) )
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
		.expectPort( PORT_INFO( "a", Bounds( "1", "0" ), Input, wire ) )
		.expectPort( PORT_INFO( "b", Bounds( "1", "0" ), Input, wire ) )
		.expectPort( PORT_INFO( "c", Bounds( "1", "0" ), Input, wire ) )
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
		.expectPort( PORT_INFO( "a", Bounds( "1", "0" ), Input, wire ) )
		.expectPort( PORT_INFO( "b", Bounds( "3", "0" ), Input, wire ) )
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
		.expectPort( PORT_INFO( "a", Bounds( "1", "0" ), Input, wire ) )
		.expectPort( PORT_INFO( "b", Bounds( "0", "3" ), Input, wire ) )
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
		.expectPort( PORT_INFO( "a", boost::none, Output, wire ) )
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
		.expectPort( PORT_INFO( "a", boost::none, Output, reg ) )
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
		.expectPort( PORT_INFO( "a", boost::none, Output, reg ) )
		.expectPort( PORT_INFO( "b", boost::none, Output, reg ) )
		.expectPort( PORT_INFO( "c", boost::none, Output, reg ) )
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
		.expectPort( PORT_INFO( "a", boost::none, Output, reg ) )
		.expectPort( PORT_INFO( "b", boost::none, Output, wire ) )
		.expectPort( PORT_INFO( "c", boost::none, Output, reg ) )
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
		.expectPort( PORT_INFO( "a", boost::none, Input, wire ) )
		.expectPort( PORT_INFO( "b", boost::none, Output, reg ) )
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
		.expectPort( PORT_INFO( "a", Bounds( "7", "0" ), Input, wire ) )
		.expectPort( PORT_INFO( "b", Bounds( "7", "0" ), Output, reg ) )
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
		.expectPort( PORT_INFO( "a", Bounds( "7", "0" ), Input, wire ) )
		.expectPort( PORT_INFO( "b", Bounds( "7", "0" ), Output, reg ) )
	.end();

	expectUnit( "top" )
		.expectPort( PORT_INFO( "a", Bounds( "7", "0" ), Input, wire ) )
		.expectPort( PORT_INFO( "b", Bounds( "7", "0" ), Output, reg ) )
	.end();
}

/***************************************************************************/

}