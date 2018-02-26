#ifndef __VLOG_DM_CONDITIONAL_EXPRESSION_HPP__
#define __VLOG_DM_CONDITIONAL_EXPRESSION_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_expression.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct ConditionalExpression
	:	public Expression
{

/***************************************************************************/

	virtual Expression const & getCondition() const = 0;

	virtual Expression const & getTrueBranch() const = 0;

	virtual Expression const & getFalseBranch() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONDITIONAL_EXPRESSION_HPP__
