#ifndef __EC_VLOG_MODULE_ITEM_IMPORTER_HPP__
#define __EC_VLOG_MODULE_ITEM_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class ModuleItemImporter
	:	public BaseImporter
{

/***************************************************************************/

public:

/***************************************************************************/

	ModuleItemImporter( VlogDM::IAccessor & _accessor );
	
/***************************************************************************/

	void importItems( Verilog2001Parser::Non_port_module_itemContext & _ctx );

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitModule_or_generate_item_declaration( 
			Verilog2001Parser::Module_or_generate_item_declarationContext * ctx 
	) override;

	antlrcpp::Any visitNet_declaration( Verilog2001Parser::Net_declarationContext * ctx ) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_MODULE_ITEM_IMPORTER_HPP__
