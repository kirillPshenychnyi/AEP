#ifndef __EC_VLOG_IDENTIFIER_IMPORTER_HPP__
#define __EC_VLOG_IDENTIFIER_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"

#include <vector>

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class IdentifierImporter
	:	public BaseImporter
{

/***************************************************************************/

	typedef
		std::vector< VlogDM::BaseIdentifierPtr >
		ExtractedIds;

/***************************************************************************/

public:

/***************************************************************************/

	IdentifierImporter( 
			VlogDM::IAccessor & _accessor 
		,	VlogDM::Writable::DesignUnit const & _targetUnit
	);

	void importIds( Verilog2001Parser::Net_assignmentContext & _ctx );

	void importId( Verilog2001Parser::Simple_hierarchical_identifierContext & _ctx );

	VlogDM::BaseIdentifierPtr takeId( int _idx );

	int getIdsCount() const;

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitNet_lvalue(
		Verilog2001Parser::Net_lvalueContext * ctx	
	) override;

	antlrcpp::Any visitNet_concatenation(
		Verilog2001Parser::Net_concatenationContext * ctx
	) override;

	antlrcpp::Any visitNet_concatenation_value(
		Verilog2001Parser::Net_concatenation_valueContext * ctx
	) override;

	antlrcpp::Any visitSimple_hierarchical_branch(
		Verilog2001Parser::Simple_hierarchical_branchContext * ctx	
	) override;

	antlrcpp::Any visitRange_expression( 
		Verilog2001Parser::Range_expressionContext  * ctx
	) override;

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any createSimpleId( antlr4::ParserRuleContext & _ctx );

/***************************************************************************/

private:

/***************************************************************************/

	ExtractedIds m_extractedIds;

	VlogDM::Writable::DesignUnit const & m_targetUnit;

	VlogDM::RangePtr m_range;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_IDENTIFIER_IMPORTER_HPP__
