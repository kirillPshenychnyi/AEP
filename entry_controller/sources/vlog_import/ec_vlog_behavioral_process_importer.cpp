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

void
BehavioralProcessImporter::importProcess( 
	Verilog2001Parser::Always_constructContext & _always 
)
{
	using namespace VlogDM;

	IAccessor & vlogDM = takeVlogDataModel();

	VlogDM::Writable::ItemsFactory const & itemsFactory 
		=	vlogDM.getObjectFactory().getItemsFactory();

	importStatement( *_always.statement() );

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

void
BehavioralProcessImporter::importStatement( 
	Verilog2001Parser::StatementContext & _statement 
)
{
	StatementImporter statementImporter( takeVlogDataModel(), takeErrorsSet() );

	statementImporter.importStatement( _statement );
	
	m_mainStatement = statementImporter.takeStatement();
	
	int controls = statementImporter.getControlsCount();

	if( controls == 0 )
		return;
		
	VlogDM::Writable::SensitivityListPtr sensList
		=	takeVlogDataModel().getObjectFactory().getItemsFactory().newSensitivityList(
				createLocation( _statement )
			);

	for( int i = 0; i < controls; ++i )
		sensList->addExpression( statementImporter.takeTimingControl( i ) );

	m_sensitivityList = std::move( sensList );
}

/***************************************************************************/

}
}
