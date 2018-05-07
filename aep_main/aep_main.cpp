#include "stdafx.h"

#include "entry_controller\api\ec_iaccessor.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "aep\api\aep_iaccessor.hpp"
#include "aep_model\api\aep_model_iaccessor.hpp"

#include "aep_main\aep_main_container_bootstrapper.hpp"
#include <iostream>

/***************************************************************************/

int main( int _argc, char* _argv[] )
{
	AepMain::ContainerBootstrapper bootstrapper;
	
	auto ec = bootstrapper.takeContainer().resolve< EntryController::IAccessor >();
	
	std::string code =
			"module top ();						\n"
		"	assign a = b + c1;					\n"
		"endmodule								\n"
	;

	Aep::IAccessor::GlobalResetParameters reset{ "rst_n", AepModel::ResetPolarity::Kind::OVL_ACTIVE_HIGH };

	bool importResult = ec->importVerilog( code );

	if( !importResult )
	{
		ec->dumpErrors( std::cout );

		return 0;
	}

	ec->runAepAnalysis(
			Aep::IAccessor::GlobalClockParameters{ "clk", AepModel::ClockEdge::Kind::OVL_POSEDGE }
		,	reset
	);

	bootstrapper.takeContainer().resolve< AepModel::IAccessor >()->regenerateAssertions( "" );
	
	return 0;
}

