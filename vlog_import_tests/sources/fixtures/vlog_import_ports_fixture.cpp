#include "stdafx.h"

#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_part_select_range.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"

#include "vlog_data_model\api\vlog_dm_declared_cast.hpp"
#include "vlog_data_model\api\vlog_dm_range_cast.hpp"
#include "vlog_data_model\api\vlog_dm_expression_cast.hpp"

#include "vlog_data_model\sources\model\vlog_dm_accessor.hpp"

#include "vlog_import_tests\sources\fixtures\vlog_import_ports_fixture.hpp"

#include "vlog_import_tests\catch.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

PortsFixture & 
PortsFixture::expectUnit( std::string const & _unit )
{
	m_unit = _unit;

	return *this;
}

/***************************************************************************/

PortsFixture &
PortsFixture::expectPort( PortInfo && _info )
{
	m_expectedPorts.emplace_back( _info );

	return *this;
}

/***************************************************************************/

void 
PortsFixture::end()
{
	using namespace VlogDM;

	IAccessor const & vlogDM = Accessor::getInstance();

	auto unit = vlogDM.findUnit( m_unit );
	REQUIRE( unit.is_initialized() );

	for( PortInfo const& info : m_expectedPorts )
		checkPort( *unit, info );
}

/***************************************************************************/

void
PortsFixture::checkPort( VlogDM::DesignUnit const& _unit, PortInfo const& _info )
{
	using namespace VlogDM;

	auto checkBound 
		=	[ this ] ( Expression const & _bound, std::string const & _expected )
			{
				PrimaryLiteral const & bound 
					= checkCast< Expression, PrimaryLiteral, ExpressionCast >( _bound );
				
				REQUIRE( bound.getValue() == _expected );
			};

	IAccessor const& vlogDm = Accessor::getInstance();
	
	auto declared = _unit.findDeclared( std::get< 0 >( _info ) );
	REQUIRE( declared.is_initialized() );

	Port const& port = checkCast< Declared, Port, DeclaredCast >( *declared );

	REQUIRE( port.getDirection() == std::get< 2 >( _info ) );
	REQUIRE( port.getNetType() == std::get< 3 >( _info ) );

	if( auto range = std::get< 1 >( _info ) )
	{
		REQUIRE( port.getDimension().is_initialized() );

		auto actualRange = port.getDimension()->getRange();
		REQUIRE( actualRange.is_initialized() );

		PartSelectRange const& boundedRange
			= checkCast< Range, PartSelectRange, RangeCast >( *actualRange );

		checkBound( boundedRange.getLeftBound(), range->first );
		checkBound( boundedRange.getRightBound(), range->second );
	}
	else
		REQUIRE( !port.getDimension().is_initialized() );
}

/***************************************************************************/

}

/***************************************************************************/