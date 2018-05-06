#ifndef __VLOG_DM_EXPRESSION_FACTORY_HPP__
#define __VLOG_DM_EXPRESSION_FACTORY_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_operator.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct ExpressionFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual ~ExpressionFactory() = default;

	virtual std::unique_ptr< PrimaryLiteral > newPrimaryLiteral(
			Location const& _location 
		,	std::string const& _value
	) const = 0;

	virtual std::unique_ptr< BinaryOperator > newBinaryOperator(
			ExpressionPtr _leftOperand
		,	ExpressionPtr _rightOperand
		,	Operator::Kind _operator
	) const = 0;

	virtual std::unique_ptr< UnaryOperator > newUnaryOperator(
			ExpressionPtr _operand
		,	Operator::Kind _operator
		,	Location const & _location
	) const = 0;

	virtual std::unique_ptr< PrimaryIdentifier > newPrimaryIdentifier(
			BaseIdentifierPtr _id
	) const = 0;

	virtual std::unique_ptr< Writable::Concatenation > newConcatenation(
		Location const & _location
	) const = 0;

	virtual std::unique_ptr< MultipleConcatenation > newMultipleConcatenation(
			ExpressionPtr _repeatExpression
		,	ConcatPtr _concat
		,	Location const & _location
	) const = 0;

	virtual std::unique_ptr< ConditionalExpression > newConditionalExpression(
			Location const & _location
		,	ExpressionPtr _condition
		,	ExpressionPtr _trueBranch
		,	ExpressionPtr _falseBranch
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}


/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_FACTORY_HPP__
