#ifndef __EC_VLOG_STATEMENT_IMPORTER_HPP__
#define __EC_VLOG_STATEMENT_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_statement.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class StatementImporter
	:	public BaseImporter
{

/***************************************************************************/

	typedef
		std::vector< VlogDM::ExpressionPtr >
		ExpressionVector;

	typedef
		std::vector< VlogDM::StatementPtr >
		StatementsVector;

	typedef
		std::set< std::string >
		Attributes;

/***************************************************************************/

public:

/***************************************************************************/

	StatementImporter( VlogDM::IAccessor & _accessor );

/***************************************************************************/

	void importStatement( Verilog2001Parser::StatementContext & ctx );

	void importStatement( Verilog2001Parser::Statement_or_nullContext & ctx );

	VlogDM::StatementPtr takeStatement();

	VlogDM::ExpressionPtr takeTimingControl( int _idx );

	int getControlsCount() const;

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitProcedural_timing_control_statement(
		Verilog2001Parser::Procedural_timing_control_statementContext * ctx 	
	) override;

	antlrcpp::Any visitDelay_or_event_control(
		Verilog2001Parser::Delay_or_event_controlContext * ctx 	
	) override;

	antlrcpp::Any visitConditional_statement( 
		Verilog2001Parser::Conditional_statementContext * ctx 
	) override;

	antlrcpp::Any visitBlocking_assignment(
	 	Verilog2001Parser::Blocking_assignmentContext * ctx 
	) override;

	antlrcpp::Any visitSeq_block(
	 	Verilog2001Parser::Seq_blockContext * ctx 
	) override;

	antlrcpp::Any visitCase_statement(
		Verilog2001Parser::Case_statementContext * ctx
	) override;

	antlrcpp::Any visitAttribute_instance(
		Verilog2001Parser::Attribute_instanceContext * ctx
	) override;

/***************************************************************************/

private:

/***************************************************************************/

	ExpressionVector m_controls;

	Attributes m_statementAttributes;

	VlogDM::Writable::StatementFactory const & m_statementFactory;

	VlogDM::StatementPtr m_resultStatement;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_STATEMENT_IMPORTER_HPP__
