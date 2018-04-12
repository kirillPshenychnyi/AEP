#include "stdafx.h"

#include "aep_main\aep_main_container_bootstrapper.hpp"

#include "entry_controller\sources\ec_accessor.hpp"
#include "vlog_data_model\sources\model\vlog_dm_accessor.hpp"
#include "aep_model\model\accessor\aep_model_accessor.hpp"

#include "aep\sources\accessor\aep_accessor.hpp"

/***************************************************************************/

namespace AepMain {

/***************************************************************************/

ContainerBootstrapper::ContainerBootstrapper()
{
	Hypodermic::ContainerBuilder builder;

	builder.registerType< VlogDM::Accessor >()
		.as< VlogDM::IAccessor >()
		.singleInstance();
	
	builder.registerType< AepModel::Accessor >()
		.as< AepModel::IAccessor >()
		.singleInstance();
	
	builder.registerType< Aep::Accessor >()
		.as< Aep::IAccessor >()
		.with< VlogDM::IAccessor>(
			[ & ]( Hypodermic::ComponentContext & _context )
			{
				return _context.resolve< VlogDM::IAccessor >();
			}
		)
		.with< AepModel::IAccessor >(
			[ & ]( Hypodermic::ComponentContext & _context )
			{
				return _context.resolve< AepModel::IAccessor >();
			}
		)
		.singleInstance();
	
	builder.registerType< EntryController::Accessor >()
		.with< VlogDM::IAccessor>(
			[ & ]( Hypodermic::ComponentContext & _context )
			{
				return _context.resolve< VlogDM::IAccessor >();
			}
		)
		.with< Aep::IAccessor>(
			[ ]( Hypodermic::ComponentContext & _context )
			{
				return _context.resolve< Aep::IAccessor >();
			}
		)
		.as< EntryController::IAccessor >()
		.singleInstance();

	m_container = builder.build();
}

/***************************************************************************/

}
