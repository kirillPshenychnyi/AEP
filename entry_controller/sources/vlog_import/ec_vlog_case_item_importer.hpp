#ifndef __EC__VLOG_CASE_ITEM_IMPORTER_HPP__
#define __EC__VLOG_CASE_ITEM_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <vector>

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class CaseItemImporter
	:	public BaseImporter
{

/***************************************************************************/

public:

/***************************************************************************/

	using BaseImporter::BaseImporter;

/***************************************************************************/

	VlogDM::BaseCaseItemPtr importCaseItem( 
		Verilog2001Parser::Case_itemContext & _caseItem 
	);

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC__VLOG_CASE_ITEM_IMPORTER_HPP__
