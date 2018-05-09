#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_module_item_importer.hpp"

#include "entry_controller\sources\vlog_import\ec_variable_importer.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_dataflow_process_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_behavioral_process_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

void 
ModuleItemImporter::importItems( 
		Verilog2001Parser::Non_port_module_itemContext & _ctx 
	)
{
	visitEachChildContext( _ctx );
}

/***************************************************************************/

void 
ModuleItemImporter::importItems( 
		Verilog2001Parser::Module_or_generate_itemContext & _ctx 
	)
{
	visitEachChildContext( _ctx );
}

/***************************************************************************/

antlrcpp::Any 
ModuleItemImporter::visitNet_declaration( 
		Verilog2001Parser::Net_declarationContext * ctx 
	)
{
	return importVar( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
ModuleItemImporter::visitReg_declaration( 
		Verilog2001Parser::Reg_declarationContext * ctx 
	)
{
	return importVar( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
ModuleItemImporter::visitContinuous_assign(
		Verilog2001Parser::Continuous_assignContext * ctx
	)
{
	DataflowProcessImporter dataflowImporter( takeVlogDataModel(), takeErrorsSet() );

	dataflowImporter.importProcess( *ctx );

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any
ModuleItemImporter::visitAlways_construct(
	Verilog2001Parser::Always_constructContext * ctx
)
{
	BehavioralProcessImporter processImporter( takeVlogDataModel(), takeErrorsSet() );

	processImporter.importProcess( *ctx );

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
ModuleItemImporter::visitModule_instantiation( 
	Verilog2001Parser::Module_instantiationContext * ctx 
)
{
	std::string const moduleId = ctx->module_identifier()->getText();

	for( auto const instance : ctx->module_instance() )
	{ 
		takeVlogDataModel().getCurrentImportedUnit().addChildInstance( 
				moduleId
			,	instance->name_of_instance()->getText()
		);
	}

	RETURN_ANY
}

/***************************************************************************/

template< typename _Context >
antlrcpp::Any
ModuleItemImporter::importVar( _Context & _ctx )
{
	VariableImporter varImporter( takeVlogDataModel(), takeErrorsSet() );

	varImporter.importVars( _ctx );

	RETURN_ANY
}

/***************************************************************************/

}
}