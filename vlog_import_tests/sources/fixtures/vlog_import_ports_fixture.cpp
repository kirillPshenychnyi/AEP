#include "stdafx.h"

#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_part_select_range.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"
#include "vlog_data_model\api\vlog_dm_variable_type.hpp"
#include "vlog_data_model\api\vlog_dm_design_unit.hpp"

#include "vlog_data_model\api\vlog_dm_declared_cast.hpp"
#include "vlog_data_model\api\vlog_dm_range_cast.hpp"
#include "vlog_data_model\api\vlog_dm_expression_cast.hpp"
#include "vlog_data_model\api\vlog_dm_type_cast.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"

#include "vlog_import_tests\sources\fixtures\vlog_import_ports_fixture.hpp"

#include "vlog_import_tests\catch.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

ContainerBootstrapper BaseFixture::m_bootstrapper;

/***************************************************************************/

PortsFixture &
PortsFixture::expectUnit( std::string const & _unit )
{
	using namespace VlogDM;

	auto vlogDM = m_bootstrapper.m_container->resolve< IAccessor >();
	
	auto unit = vlogDM->findUnit( _unit );
	REQUIRE( unit.is_initialized() );

	m_currentUnit = unit.get_ptr();

	return *this;
}

/***************************************************************************/

PortsFixture::PortHelper &
PortsFixture::expectPort( std::string const & _name )
{
	using namespace VlogDM;

	auto declared = m_currentUnit->findDeclared( _name );
	REQUIRE( declared.is_initialized() );
	Port const& port = checkCast< Declared, Port, DeclaredCast >( *declared );

	m_expectedPorts.emplace_back( 
		std::make_unique< PortHelper >( *this, port )
	);

	return *m_expectedPorts.back();
}

/***************************************************************************/

PortsFixture::PortHelper::PortHelper( 
		PortsFixture & _parent
	,	VlogDM::Port const & _port 
	)
	:	m_parent( _parent )
	,	m_port( _port )
{

}

/***************************************************************************/

PortsFixture::PortHelper & 
PortsFixture::PortHelper::expectBounds( std::string const& _left, std::string const& _right )
{
	using namespace VlogDM;

	auto checkBound 
		=	[ this ] ( Expression const & _bound, std::string const & _expected )
			{
				PrimaryLiteral const & bound 
					= checkCast< Expression, PrimaryLiteral, ExpressionCast >( _bound );
				
				REQUIRE( bound.getValue() == _expected );
			};

	auto dimension = m_port.getType().getDimension();

	REQUIRE( dimension.is_initialized() );

	auto actualRange = dimension->getRange();
	REQUIRE( actualRange.is_initialized() );

	PartSelectRange const& boundedRange
			= checkCast< Range, PartSelectRange, RangeCast >( *actualRange );

	checkBound( boundedRange.getLeftBound(), _left );
	checkBound( boundedRange.getRightBound(), _right );

	return *this;
}

/***************************************************************************/

PortsFixture::PortHelper & 
PortsFixture::PortHelper::expectNetType( VlogDM::NetKind::Kind _kind ) 
{
	using namespace VlogDM;

	checkType< NetType, NetKind >( _kind );
	
	return *this;
}

/***************************************************************************/

PortsFixture::PortHelper & 
PortsFixture::PortHelper::expectRegType()
{
	using namespace VlogDM;
	
	checkType< VariableType, VariableKind >( VariableKind::Kind::reg );
	
	return *this;
}

/***************************************************************************/

template < typename _TargetType, class _Kind >
void
PortsFixture::PortHelper::checkType( typename _Kind::Kind _kind )
{
	using namespace VlogDM;

	_TargetType const & type
		= BaseFixture::checkCast< Type, _TargetType, TypeCast >( m_port.getType() );

	REQUIRE( _kind == type.getKind() );
}

/***************************************************************************/

PortsFixture::PortHelper & 
PortsFixture::PortHelper::expectDirection( 
		VlogDM::PortDirection::Direction _direction 
)
{
	REQUIRE( _direction == m_port.getDirection() );

	return *this;
}

/***************************************************************************/

PortsFixture & 
PortsFixture::PortHelper::end()
{
	return m_parent;
}

/***************************************************************************/

}

/***************************************************************************/