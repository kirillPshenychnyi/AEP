#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_expression_factory_impl.hpp"

#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"

#include "vlog_data_model\sources\model\vlog_dm_primary_literal_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_binary_operator_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_unary_operator_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_primary_identifier_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_concatenation_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_multiple_concatenation_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_conditional_expression_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

std::unique_ptr< PrimaryLiteral > 
ExpressionFactoryImpl::newPrimaryLiteral( 
		Location const & _location
	,	std::string const& _value
) const
{
	return std::make_unique< PrimaryLiteralImpl >( _location, _value );
}

/***************************************************************************/

std::unique_ptr< BinaryOperator > 
ExpressionFactoryImpl::newBinaryOperator(
		ExpressionPtr _leftOperand
	,	ExpressionPtr _rightOperand
	,	Operator::Kind _operator
) const
{
	return 
		std::make_unique< BinaryOperatorImpl >( 
				_leftOperand->getLocation()
			,	std::move( _leftOperand )
			,	std::move( _rightOperand )
			,	_operator 
		);
}

/***************************************************************************/

std::unique_ptr< UnaryOperator >
ExpressionFactoryImpl::newUnaryOperator( 
		ExpressionPtr _operand
	,	Operator::Kind _operator
	,	Location const & _location
) const
{
	return 
		std::make_unique< UnaryOperatorImpl >( 
				std::move( _operand )
			,	_operator
			,	_location 
		);
}

/***************************************************************************/

std::unique_ptr< PrimaryIdentifier > 
ExpressionFactoryImpl::newPrimaryIdentifier( BaseIdentifierPtr _id ) const
{
	return 
		std::make_unique< PrimaryIdentifierImpl >( 
				_id->getLocation()
			,	std::move( _id ) 
		);
}

/***************************************************************************/

std::unique_ptr< Writable::Concatenation > 
ExpressionFactoryImpl::newConcatenation( Location const & _location ) const
{
	return std::make_unique< ConcatenationImpl >( _location );
}

/***************************************************************************/

std::unique_ptr< MultipleConcatenation > 
ExpressionFactoryImpl::newMultipleConcatenation(
		ExpressionPtr _repeatExpression
	,	ConcatPtr _concat
	,	Location const & _location
) const
{
	return
		std::make_unique< MultipleConcatenationImpl >(
				std::move( _concat )
			,	std::move( _repeatExpression )
			,	_location 
		);
}

/***************************************************************************/

std::unique_ptr< ConditionalExpression > 
ExpressionFactoryImpl::newConditionalExpression( 
		Location const & _location
	,	ExpressionPtr _condition
	,	ExpressionPtr _trueBranch
	,	ExpressionPtr _falseBranch 
) const
{
	return 
		std::make_unique< ConditionalExpressionImpl >(
				_location
			,	std::move( _condition )
			,	std::move( _trueBranch )
			,	std::move( _falseBranch )
		);
}

/***************************************************************************/

}
