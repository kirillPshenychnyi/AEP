#include "stdafx.h"

#include "entry_controller\vlog_import\ec_vlog_design_unit_importer.hpp"
#include "entry_controller\vlog_import\ec_vlog_port_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_design_unit_factory.hpp"

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
	using namespace VlogDM;

	Writable::DesignUnitFactory const& unitsFactory = getVlogDataModel().getDesignUnitFactory();

	for( auto child : ctx->children )
	{
		m_units.emplace_back( unitsFactory.newDesignUnit( "m", createLocation( *ctx ) ) );

		child->accept( this );
	}

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
DesingUnitImporter::visitList_of_ports( Verilog2001Parser::List_of_portsContext *ctx ) 
{	
	PortImporter portImporter( getVlogDataModel(), *m_units.back().get() );

	portImporter.importPorts( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
DesingUnitImporter::visitList_of_port_declarations( Verilog2001Parser::List_of_port_declarationsContext * ctx )
{
	using namespace VlogDM;
	
	PortImporter portImporter( getVlogDataModel(), *m_units.back() );
	portImporter.importPorts( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}