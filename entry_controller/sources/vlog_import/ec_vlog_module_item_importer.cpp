#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_module_item_importer.hpp"

#include "entry_controller\sources\vlog_import\ec_variable_importer.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_dataflow_process_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_behavioral_process_importer.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

ModuleItemImporter::ModuleItemImporter( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
{
}

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
ModuleItemImporter::visitModule_or_generate_item(
	Verilog2001Parser::Module_or_generate_itemContext * ctx
)
{
	visitEachChildContext( *ctx );
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ModuleItemImporter::visitModule_or_generate_item_declaration( 
		Verilog2001Parser::Module_or_generate_item_declarationContext *ctx 
	) 
{
	visitEachChildContext( *ctx );
	return antlrcpp::Any();
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
	DataflowProcessImporter dataflowImporter( getVlogDataModel() );

	dataflowImporter.importProcess( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
ModuleItemImporter::visitAlways_construct(
	Verilog2001Parser::Always_constructContext * ctx
)
{
	BehavioralProcessImporter processImporter( getVlogDataModel() );

	processImporter.importProcess( *ctx );

	return antlrcpp::Any();
}


/***************************************************************************/

template< typename _Context >
antlrcpp::Any
ModuleItemImporter::importVar( _Context & _ctx )
{
	VariableImporter varImporter( getVlogDataModel() );

	varImporter.importVars( _ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}