#ifndef __VLOG_DM_EXPRESSION_FACTORY_IMPL_HPP__
#define __VLOG_DM_EXPRESSION_FACTORY_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ExpressionFactoryImpl
	:	public Writable::ExpressionFactory
{

/***************************************************************************/

public:

/***************************************************************************/

	std::unique_ptr< PrimaryLiteral > newPrimaryLiteral(
			Location const& _location 
		,	std::string const& _value
	) const override;

	std::unique_ptr< BinaryOperator > newBinaryOperator(
			ExpressionPtr _leftOperand
		,	ExpressionPtr _rightOperand
		,	Operator::Kind _operator
	) const override;

	std::unique_ptr< UnaryOperator > newUnaryOperator(
			ExpressionPtr _operand
		,	Operator::Kind _operator
		,	Location const & _location
	) const override;

	std::unique_ptr< PrimaryIdentifier > newPrimaryIdentifier(
		BaseIdentifierPtr _id
	) const override;

	std::unique_ptr< Writable::Concatenation > newConcatenation(
		Location const & _location
	) const override;

	std::unique_ptr< MultipleConcatenation > newMultipleConcatenation(
			ExpressionPtr _repeatExpression
		,	ConcatPtr _concat
		,	Location const & _location
	) const override;

	std::unique_ptr< ConditionalExpression > newConditionalExpression(
			Location const & _location
		,	ExpressionPtr _condition
		,	ExpressionPtr _trueBranch
		,	ExpressionPtr _falseBranch
	) const override;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_FACTORY_IMPL_HPP__
