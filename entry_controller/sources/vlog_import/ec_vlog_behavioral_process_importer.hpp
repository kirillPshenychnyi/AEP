#ifndef __VLOG_BEHAVIORAL_PROCESS_IMPORT_HPP__
#define __VLOG_BEHAVIORAL_PROCESS_IMPORT_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_statement.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_sensitivity_list.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class BehavioralProcessImporter
	:	public BaseImporter
{

/***************************************************************************/

public:

/***************************************************************************/

	BehavioralProcessImporter( VlogDM::IAccessor & _accessor );

/***************************************************************************/

	void importProcess( 
		Verilog2001Parser::Always_constructContext & _always 
	);

/***************************************************************************/

private:

/***************************************************************************/

	void importStatement( Verilog2001Parser::StatementContext & _statement );

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::StatementPtr m_mainStatement;

	VlogDM::SensitivityListPtr m_sensitivityList;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_BEHAVIORAL_PROCESS_IMPORT_HPP__
