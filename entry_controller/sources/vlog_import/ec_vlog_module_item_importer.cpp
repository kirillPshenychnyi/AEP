#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_module_item_importer.hpp"

#include "entry_controller\sources\vlog_import\ec_variable_importer.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

ModuleItemImporter::ModuleItemImporter( 
		VlogDM::IAccessor & _accessor 
	,	VlogDM::Writable::DesignUnit & _targetUnit
	)
	:	BaseImporter( _accessor )
	,	m_targetUnit( _targetUnit )
{
}

void 
ModuleItemImporter::importItems( 
		Verilog2001Parser::Non_port_module_itemContext & _ctx 
	)
{
	acceptEachChildContext( _ctx );
}

/***************************************************************************/

void 
ModuleItemImporter::importItems( 
		Verilog2001Parser::Module_or_generate_itemContext & _ctx 
	)
{
	acceptEachChildContext( _ctx );
}

/***************************************************************************/

antlrcpp::Any 
ModuleItemImporter::visitModule_or_generate_item(
	Verilog2001Parser::Module_or_generate_itemContext * ctx
)
{
	acceptEachChildContext( *ctx );
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ModuleItemImporter::visitModule_or_generate_item_declaration( 
		Verilog2001Parser::Module_or_generate_item_declarationContext *ctx 
	) 
{
	acceptEachChildContext( *ctx );
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
visitContinuous_assign(
		Verilog2001Parser::Continuous_assignContext * ctx
	)
{

}

/***************************************************************************/

template< typename _Context >
antlrcpp::Any
ModuleItemImporter::importVar( _Context & _ctx )
{
	VariableImporter varImporter( getVlogDataModel(), m_targetUnit );

	varImporter.importVars( _ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}