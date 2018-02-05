#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_design_unit_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_port_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_module_item_importer.hpp"

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
DesingUnitImporter::visitModule_declaration(
		Verilog2001Parser::Module_declarationContext * ctx 
	)
{
	using namespace VlogDM;
	
	Writable::DesignUnitFactory const& unitsFactory = getVlogDataModel().getDesignUnitFactory();

	m_currentUnit 
		=	std::move( unitsFactory.newDesignUnit( ctx->children[ 1 ]->getText(), createLocation( *ctx ) ) );

	acceptEachChildContext( *ctx );

	IAccessor & vlogDm = getVlogDataModel();

	vlogDm.addUnit( std::move( m_currentUnit ) );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
DesingUnitImporter::visitModule_item(
		Verilog2001Parser::Module_itemContext *ctx 
	)	 
{	
	acceptEachChildContext( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any DesingUnitImporter::visitPort_declaration(
		Verilog2001Parser::Port_declarationContext * ctx 
	)
{
	PortImporter portImporter( getVlogDataModel(), *m_currentUnit );
	portImporter.importPorts( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
DesingUnitImporter::visitList_of_port_declarations( 
		Verilog2001Parser::List_of_port_declarationsContext * ctx 
	)
{	
	PortImporter portImporter( getVlogDataModel(), *m_currentUnit );
	portImporter.importPorts( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
DesingUnitImporter::visitModule_or_generate_item( 
		Verilog2001Parser::Module_or_generate_itemContext *ctx
	)
{
	return importItem( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
DesingUnitImporter::visitNon_port_module_item(
		Verilog2001Parser::Non_port_module_itemContext * ctx 
	)
{
	return importItem( *ctx );
}

/***************************************************************************/

template< typename _Context >
antlrcpp::Any 
DesingUnitImporter::importItem( _Context & _ctx )
{
	ModuleItemImporter itemImporter( getVlogDataModel(), *m_currentUnit );

	itemImporter.importItems( _ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}