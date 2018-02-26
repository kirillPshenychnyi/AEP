#ifndef __EC_VLOG_DESIGN_UNIT_IMPORTER_HPP__
#define __EC_VLOG_DESIGN_UNIT_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

#include <vector>

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class DesingUnitImporter
	:	public BaseImporter
{

/***************************************************************************/

public:

/***************************************************************************/

	DesingUnitImporter( VlogDM::IAccessor & _accessor );

/***************************************************************************/

	antlrcpp::Any visitModule_declaration( 
		Verilog2001Parser::Module_declarationContext *ctx 
	) override;

	antlrcpp::Any visitModule_item( 
		Verilog2001Parser::Module_itemContext *ctx 
	) override;

	antlrcpp::Any visitPort_declaration( 
		Verilog2001Parser::Port_declarationContext *ctx 
	) override;

	antlrcpp::Any visitList_of_port_declarations( 
		Verilog2001Parser::List_of_port_declarationsContext  *ctx 
	) override;

	antlrcpp::Any visitNon_port_module_item( 
		Verilog2001Parser::Non_port_module_itemContext *ctx 
	) override;

	antlrcpp::Any visitModule_or_generate_item( 
		Verilog2001Parser::Module_or_generate_itemContext *ctx
	) override;
	
/***************************************************************************/

	template< typename _Context >
	antlrcpp::Any importItem( _Context & _ctx );

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_DESIGN_UNIT_IMPORTER_HPP__
