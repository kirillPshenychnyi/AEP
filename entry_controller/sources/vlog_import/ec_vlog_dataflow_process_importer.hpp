#ifndef __EC_VLOG_DATAFLOW_PROCESS_IMPORTER_HPP__
#define __EC_VLOG_DATAFLOW_PROCESS_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class DataflowProcessImporter
	:	public BaseImporter
{

/***************************************************************************/

public:

/***************************************************************************/

	using BaseImporter::BaseImporter;

/***************************************************************************/

	void importProcess( Verilog2001Parser::Continuous_assignContext & _ctx );

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitNet_assignment(
		Verilog2001Parser::Net_assignmentContext * ctx 
	) override;

	antlrcpp::Any visitExpression(
		Verilog2001Parser::ExpressionContext * ctx	
	) override;

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::Location m_processLocation;

	VlogDM::ExpressionPtr m_targetExpression;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_DATAFLOW_PROCESS_IMPORTER_HPP__
