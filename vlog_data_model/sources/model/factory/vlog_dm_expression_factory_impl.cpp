#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_expression_factory_impl.hpp"

#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"

#include "vlog_data_model\sources\model\vlog_dm_primary_literal_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_binary_operator_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_primary_identifier_impl.hpp"

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
	,	Operator::Enum _operator
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

std::unique_ptr< PrimaryIdentifier > 
ExpressionFactoryImpl::newPrimaryIdentifier( BaseIdentifierPtr _id ) const
{
	return std::make_unique< PrimaryIdentifierImpl >( _id->getLocation(), std::move( _id ) );
}

/***************************************************************************/

}
