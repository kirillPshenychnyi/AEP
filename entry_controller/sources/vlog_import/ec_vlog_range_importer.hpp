#ifndef __EC_VLOG_RANGE_IMPORTER_HPP__
#define __EC_VLOG_RANGE_IMPORTER_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_expression.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class RangeImporter
	:	public BaseImporter
{
	
/***************************************************************************/

public:

/***************************************************************************/

	using BaseImporter::BaseImporter;
	
/***************************************************************************/

	VlogDM::RangePtr importRange( 
		Verilog2001Parser::Range_expressionContext & _rangeExpression 
	);

/***************************************************************************/

	antlrcpp::Any visitExpression( 
		Verilog2001Parser::ExpressionContext * ctx 
	) override;

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::ExpressionPtr m_lsbExpression;

	VlogDM::ExpressionPtr m_msbExpression;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_RANGE_IMPORTER_HPP__
