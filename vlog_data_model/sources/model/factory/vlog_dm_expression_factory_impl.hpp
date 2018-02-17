#ifndef __VLOG_DM_EXPRESSION_FACTORY_IMPL_HPP__
#define __VLOG_DM_EXPRESSION_FACTORY_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

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
	
	std::unique_ptr< PrimaryIdentifier > newPrimaryIdentifier(
			BaseIdentifierPtr _id
	) const override;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_FACTORY_IMPL_HPP__
