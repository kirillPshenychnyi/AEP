#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_behavioral_process_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_statement_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_sensitivity_list.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

BehavioralProcessImporter::BehavioralProcessImporter( 
		VlogDM::IAccessor & _accessor 
	)
	:	BaseImporter( _accessor )
{
}

/***************************************************************************/

void
BehavioralProcessImporter::importProcess( 
	Verilog2001Parser::Always_constructContext & _always 
)
{
	using namespace VlogDM;

	visitEachChildContext( _always );

	IAccessor & vlogDM = getVlogDataModel();

	VlogDM::Writable::ItemsFactory const & itemsFactory 
		=	vlogDM.getObjectFactory().getItemsFactory();

	assert( m_mainStatement );
	
	vlogDM.getCurrentImportedUnit().addProcess(
		itemsFactory.newBehavioralProcess(
				createLocation( _always )
			,	std::move( m_mainStatement )
			,	std::move( m_sensitivityList )
		)
	);
}

/***************************************************************************/

antlrcpp::Any 
BehavioralProcessImporter::visitStatement( Verilog2001Parser::StatementContext * ctx )
{
	StatementImporter statementImporter( getVlogDataModel() );

	statementImporter.importStatement( *ctx );
	
	m_mainStatement = statementImporter.takeStatement();
	
	int controls = statementImporter.getControlsCount();

	if( controls == 0 )
		RETURN_ANY
		
	VlogDM::Writable::SensitivityListPtr sensList
		=	getVlogDataModel().getObjectFactory().getItemsFactory().newSensitivityList(
				createLocation( *ctx )
			);

	for( int i = 0; i < controls; ++i )
		sensList->addExpression( statementImporter.takeTimingControl( i ) );

	m_sensitivityList = std::move( sensList );

	RETURN_ANY
}

/***************************************************************************/

}
}
