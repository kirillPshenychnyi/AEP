#ifndef __VLOG_DM_BINARY_OPERATOR_HPP__
#define __VLOG_DM_BINARY_OPERATOR_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_expression.hpp"

#include "vlog_data_model\api\vlog_dm_operator.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct BinaryOperator
	:	public Expression
{

/***************************************************************************/

	virtual Expression const & getLeftOperand() const = 0;

	virtual Expression const & getRightOperand() const = 0;

	virtual Operator::Kind getOperator() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // __VLOG_DM_BINARY_OPERATOR_HPP__
