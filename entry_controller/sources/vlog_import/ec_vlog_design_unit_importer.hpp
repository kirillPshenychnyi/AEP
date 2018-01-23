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

	antlrcpp::Any visitModule_declaration( Verilog2001Parser::Module_declarationContext *ctx ) override;

	antlrcpp::Any visitList_of_ports( Verilog2001Parser::List_of_portsContext *ctx ) override;

	antlrcpp::Any visitList_of_port_declarations( Verilog2001Parser::List_of_port_declarationsContext  *ctx ) override;

/***************************************************************************/

	std::unique_ptr< VlogDM::Writable::DesignUnit > m_currentUnit;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_DESIGN_UNIT_IMPORTER_HPP__
