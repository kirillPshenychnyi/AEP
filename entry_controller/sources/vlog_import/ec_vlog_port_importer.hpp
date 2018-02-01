#ifndef __VLOG_PORT_IMPORTER_HPP__
#define __VLOG_PORT_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_net_importer.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declaration.hpp"

#include "vlog_data_model\api\vlog_dm_port_directrion.hpp"

#include <vector>

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class PortImporter
	:	public BaseNetImporter< VlogDM::Writable::PortDeclaration >
{

/***************************************************************************/

	typedef
		BaseNetImporter< VlogDM::Writable::PortDeclaration >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	PortImporter( 
			VlogDM::IAccessor & _accessor
		,	VlogDM::Writable::DesignUnit & _targetUnit 
	);

	void importPorts( Verilog2001Parser::Port_declarationContext & _ctx );
	
	void importPorts( const Verilog2001Parser::List_of_port_declarationsContext & _ctx );

/***************************************************************************/

private:

/***************************************************************************/

	template< typename _PortDeclarationContext >
	void importPorts( 
			_PortDeclarationContext &
		,	VlogDM::PortDirection::Direction _direction 
	);

/***************************************************************************/

	antlrcpp::Any visitList_of_port_declarations( Verilog2001Parser::List_of_port_declarationsContext *ctx ) override;

	antlrcpp::Any visitPort_declaration( Verilog2001Parser::Port_declarationContext *ctx ) override;

	antlrcpp::Any visitInout_declaration( Verilog2001Parser::Inout_declarationContext *ctx ) override;
	
	antlrcpp::Any visitInput_declaration( Verilog2001Parser::Input_declarationContext *ctx ) override;

	antlrcpp::Any visitOutput_declaration( Verilog2001Parser::Output_declarationContext *ctx ) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // __VLOG_PORT_IMPORTER_HPP__