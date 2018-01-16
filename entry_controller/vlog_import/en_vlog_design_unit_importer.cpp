#include "stdafx.h"

#include "entry_controller\vlog_import\ec_vlog_design_unit_importer.hpp"
#include "entry_controller\vlog_import\ec_vlog_dm_port_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"

/***************************************************************************/

namespace EntryController{ 
namespace VlogImport {

/***************************************************************************/

DesingUnitImporter::DesingUnitImporter( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
{

}

/***************************************************************************/

antlrcpp::Any
DesingUnitImporter::visitModule_declaration( Verilog2001Parser::Module_declarationContext * ctx )
{
	for( auto child : ctx->children )
		child->accept( this );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
DesingUnitImporter::visitList_of_ports( Verilog2001Parser::List_of_portsContext *ctx ) 
{	
	PortImporter portImporter( getVlogDataModel() );

	portImporter.importPorts( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
DesingUnitImporter::visitList_of_port_declarations( Verilog2001Parser::List_of_port_declarationsContext * ctx )
{
	PortImporter portImporter( getVlogDataModel() );

	portImporter.importPorts( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}