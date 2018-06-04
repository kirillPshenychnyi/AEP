#ifndef __VLOG_DM_EXPRESSION_CALCULATOR_HPP__
#define __VLOG_DM_EXPRESSION_CALCULATOR_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace VlogDM {
namespace VlogEngines { 

/***************************************************************************/

class BitwidthCalculator
	:	public ExpressionVisitor
{ 

/***************************************************************************/

public:

/***************************************************************************/

	BitwidthCalculator();

	int calculate( Expression const & _expression );

	int calculate( Declared const & _declared );

/***************************************************************************/

private:

/***************************************************************************/

	void visit( PrimaryLiteral const & _literal );

	void visit( BinaryOperator const & _operator );

	void visit( UnaryOperator const & _operator );

	void visit( PrimaryIdentifier const & _id );

	void visit( Concatenation const & _concat );

	void visit( MultipleConcatenation const & _concat );

	void visit( ConditionalExpression const & _conditional );

/***************************************************************************/

	void calculateMaxOfBinary( BinaryOperator const & _binary );

	void reset();

/***************************************************************************/

private:

/***************************************************************************/

	int m_result;

	static const int m_sSingleBitWidth;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_CALCULATOR_HPP__
