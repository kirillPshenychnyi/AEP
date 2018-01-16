#ifndef __EC_VLOG_DESIGN_UNIT_IMPORTER_HPP__
#define __EC_VLOG_DESIGN_UNIT_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\vlog_import\ec_vlog_base_importer.hpp"

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

	antlrcpp::Any visitModule_declaration( Verilog2001Parser::Module_declarationContext *ctx ) override;

	antlrcpp::Any visitList_of_ports( Verilog2001Parser::List_of_portsContext *ctx ) override;

	antlrcpp::Any visitList_of_port_declarations( Verilog2001Parser::List_of_port_declarationsContext  *ctx ) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_DESIGN_UNIT_IMPORTER_HPP__
