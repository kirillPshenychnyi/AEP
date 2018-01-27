#ifndef __VLOG_IMPORT_PORTS_FIXTURE_HPP__
#define __VLOG_IMPORT_PORTS_FIXTURE_HPP__

/***************************************************************************/

#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

#include "vlog_data_model\api\vlog_dm_port_directrion.hpp"

#include "vlog_data_model\api\vlog_dm_net_kind.hpp"

/***************************************************************************/

namespace VlogDM {

	struct DesignUnit;
	struct Port;
}

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

class PortsFixture
	:	public BaseFixture
{

/***************************************************************************/

	struct PortHelper
	{
		typedef
			std::unique_ptr< PortHelper >
			Ptr;

		PortHelper( PortsFixture & _parent, VlogDM::Port const & _port );

		PortHelper & expectBounds( std::string const & _left, std::string const & _right );

		PortHelper & expectNetType( VlogDM::NetKind::Kind _kind );

		PortHelper & expectRegType();

		PortHelper & expectDirection( VlogDM::PortDirection::Direction _direction );

		PortsFixture & end();

		template < typename _TargetType, class _Kind >
		void checkType( typename _Kind::Kind _kind );

		PortsFixture & m_parent;
		VlogDM::Port const & m_port;
	};

/***************************************************************************/

public:

/***************************************************************************/

	typedef
		std::vector< PortHelper::Ptr >
		ExpectedPorts;

/***************************************************************************/

	PortsFixture & expectUnit( std::string const & _unit );

	PortHelper & expectPort( std::string const & _name );

/***************************************************************************/

private:

/***************************************************************************/

	ExpectedPorts m_expectedPorts;

	const VlogDM::DesignUnit * m_currentUnit;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_IMPORT_PORTS_FIXTURE_HPP__
