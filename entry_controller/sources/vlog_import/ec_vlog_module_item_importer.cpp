#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_net_extractor.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_module_item_importer.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

ModuleItemImporter::ModuleItemImporter( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
{
}

void 
ModuleItemImporter::importItems( Verilog2001Parser::Non_port_module_itemContext & _ctx )
{
	acceptEachChildContext( _ctx );
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
ModuleItemImporter::visitNet_declaration( Verilog2001Parser::Net_declarationContext * ctx )
{
	NetExtractor extractor( getVlogDataModel() );

	extractor.extract( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}