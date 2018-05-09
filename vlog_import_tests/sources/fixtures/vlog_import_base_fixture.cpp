
#include "stdafx.h"

#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

#include "entry_controller\sources\ec_accessor.hpp"
#include "vlog_data_model\sources\model\vlog_dm_accessor.hpp"
#include "aep\api\aep_iaccessor.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

ContainerBootstrapper::ContainerBootstrapper()
{
	Hypodermic::ContainerBuilder builder;

	builder.registerType< VlogDM::Accessor >()
		.as< VlogDM::IAccessor >()
		.singleInstance();

	builder.registerType< EntryController::Accessor >()
		.with< VlogDM::IAccessor>(
			[ & ]( Hypodermic::ComponentContext & _context )
			{
				return _context.resolve< VlogDM::IAccessor >();
			}
		)
		.with< Aep::IAccessor >(
			[ & ]( Hypodermic::ComponentContext & _context )
			{
				// Not used in dm tests
				return std::shared_ptr< Aep::IAccessor >();
			}
		)
		.as< EntryController::IAccessor >()
		.singleInstance();

	m_container = builder.build();
}

/***************************************************************************/

VlogDM::IAccessor const & 
BaseFixture::getVlogDm() const
{
	return *m_bootstrapper.m_container->resolve< VlogDM::IAccessor >();
}

/***************************************************************************/

EntryController::IAccessor const & 
BaseFixture::getEntryController() const
{
	return *m_bootstrapper.m_container->resolve< EntryController::IAccessor >();
}

/***************************************************************************/

void 
BaseFixture::runImport( std::string const & _code )
{
	m_bootstrapper.m_container->resolve< EntryController::IAccessor >()->importVerilog( _code );
}

/***************************************************************************/

}
