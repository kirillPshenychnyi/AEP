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

	struct BinaryOperatoInfo
	{
		BinaryOperatoInfo()
			:	m_operator( VlogDM::Operator::Kind::Unknown )
		{}

		void clear()
		{
			m_leftOperand.reset();
			m_rightOperand.reset();
			m_operator = VlogDM::Operator::Kind::Unknown;
		}

		void addOperand( VlogDM::ExpressionPtr _expression )
		{
			if( !m_leftOperand )
				m_leftOperand = std::move( _expression );
			else 
				m_rightOperand = std::move( _expression );
		}

		VlogDM::ExpressionPtr getValidOperand()
		{
			return 
				m_leftOperand 
				?	std::move( m_leftOperand ) 
				:	std::move( m_rightOperand );
		}

		bool canConstructBinaryOperator()
		{
			return m_leftOperand && m_rightOperand;
		}

		VlogDM::ExpressionPtr m_leftOperand;
		VlogDM::ExpressionPtr m_rightOperand;
		VlogDM::Operator::Kind m_operator;
	};

/***************************************************************************/

	typedef
		std::vector< VlogDM::ExpressionPtr >
		Operands;

	typedef
		std::list < VlogDM::Operator::Kind >
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

	VlogDM::RangePtr importRange(
		Verilog2001Parser::Range_expressionContext & _rangeExpression
	);

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::ExpressionPtr createExpression();

	VlogDM::ExpressionPtr createBinaryOperator( BinaryOperatoInfo & _info );

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitSimple_hierarchical_identifier(
			Verilog2001Parser::Simple_hierarchical_identifierContext * ctx
	) override;

	antlrcpp::Any visitTerm( Verilog2001Parser::TermContext * ctx ) override;

	antlrcpp::Any visitPrimary( Verilog2001Parser::PrimaryContext * ctx ) override;

	antlrcpp::Any visitBinary_operator( 
		Verilog2001Parser::Binary_operatorContext * ctx 
	) override;

	antlrcpp::Any visitNumber( 
		Verilog2001Parser::NumberContext * ctx 
	) override;

/***************************************************************************/

private:

/***************************************************************************/

	Operands m_topNodes;

	Operators m_operators;

	BinaryOperatoInfo m_currentInfo;

	VlogDM::Writable::DesignUnit const & m_targetUnit;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_EXPRESSION_IMPORTER_HPP__
