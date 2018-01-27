#ifndef __VLOG_PORT_IMPORTER_HPP__
#define __VLOG_PORT_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declaration.hpp"

#include "vlog_data_model\api\vlog_dm_port_directrion.hpp"

#include <vector>

/***************************************************************************/

namespace VlogDM
{
	namespace Writable
	{
		struct DesignUnit;
	}

	struct Dimension;
	struct Type;
}

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class PortImporter
	:	public BaseImporter
{

/***************************************************************************/

	typedef
		std::unique_ptr< VlogDM::Writable::PortDeclaration >
		PortDeclarationPtr;

	typedef
		std::vector< PortDeclarationPtr >
		ExtractedDeclarations;
	
/***************************************************************************/

	struct PortDeclarationInfoExtractror;

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

	std::unique_ptr< VlogDM::Dimension > createDimension( 
			PortDeclarationInfoExtractror const& _extractor 
	);

	std::unique_ptr< VlogDM::Type > createType( 
			PortDeclarationInfoExtractror const& _extractor 
	);

/***************************************************************************/

	antlrcpp::Any visitList_of_port_declarations( Verilog2001Parser::List_of_port_declarationsContext *ctx ) override;

	antlrcpp::Any visitPort_declaration( Verilog2001Parser::Port_declarationContext *ctx ) override;

	antlrcpp::Any visitInout_declaration( Verilog2001Parser::Inout_declarationContext *ctx ) override;
	
	antlrcpp::Any visitInput_declaration( Verilog2001Parser::Input_declarationContext *ctx ) override;

	antlrcpp::Any visitOutput_declaration( Verilog2001Parser::Output_declarationContext *ctx ) override;

/***************************************************************************/

private:

/***************************************************************************/

	ExtractedDeclarations m_extractedDeclarations;

	VlogDM::Writable::DesignUnit & m_targetUnit;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // __VLOG_PORT_IMPORTER_HPP__