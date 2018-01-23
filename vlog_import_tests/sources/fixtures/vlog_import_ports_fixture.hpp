#ifndef __VLOG_IMPORT_PORTS_FIXTURE_HPP__
#define __VLOG_IMPORT_PORTS_FIXTURE_HPP__

/***************************************************************************/

#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

#include "vlog_data_model\api\vlog_dm_port_directrion.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"

#include <tuple>

/***************************************************************************/

namespace VlogDM {

	struct DesignUnit;

}

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

class PortsFixture
	:	public BaseFixture
{

/***************************************************************************/

public:

/***************************************************************************/

	typedef
		std::pair< std::string, std::string >
		Bounds;

	typedef
		std::tuple< 
			std::string
		,	boost::optional< Bounds >
		,	VlogDM::PortDirection::Direction 
		,	VlogDM::NetType::Type
		>
		PortInfo;

	typedef
		std::vector< PortInfo >
		ExpectedPorts;

/***************************************************************************/

	PortsFixture & expectUnit( std::string const & _unit );

	PortsFixture & expectPort( PortInfo && _info );

	void end();

/***************************************************************************/

private:

/***************************************************************************/

	void checkPort( VlogDM::DesignUnit const& _unit, PortInfo const & _info );

/***************************************************************************/

private:

/***************************************************************************/

	ExpectedPorts m_expectedPorts;

	std::string m_unit;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_IMPORT_PORTS_FIXTURE_HPP__
