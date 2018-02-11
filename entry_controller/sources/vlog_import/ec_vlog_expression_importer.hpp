#ifndef __EC_VLOG_EXPRESSION_IMPORTER_HPP__
#define __EC_VLOG_EXPRESSION_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_operator.hpp"

#include <list>

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class ExpressionImporter
	:	public BaseImporter
{

/***************************************************************************/

	typedef
		std::list< VlogDM::ExpressionPtr >
		Primes;

	typedef
		std::list< VlogDM::Operator::Enum >
		Operators;

/***************************************************************************/

public:

/***************************************************************************/

	ExpressionImporter( 
			VlogDM::IAccessor & _vlogDm
		,	VlogDM::Writable::DesignUnit const & _targetUnit
	);

	VlogDM::ExpressionPtr importExpression( 
			Verilog2001Parser::ExpressionContext & _expression
	);

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitSimple_hierarchical_identifier(
			Verilog2001Parser::Simple_hierarchical_identifierContext * ctx
	) override;

	antlrcpp::Any visitTerm( Verilog2001Parser::TermContext * ctx ) override;

	antlrcpp::Any visitPrimary( Verilog2001Parser::PrimaryContext * ctx ) override;

/***************************************************************************/

private:

/***************************************************************************/

	Primes m_primes;

	Operators m_operators;

	VlogDM::Writable::DesignUnit const & m_targetUnit;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_EXPRESSION_IMPORTER_HPP__
