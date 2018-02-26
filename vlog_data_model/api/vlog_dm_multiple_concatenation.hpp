#ifndef __VLOG_DM_MULTIPLE_CONCATENATION_HPP__
#define __VLOG_DM_MULTIPLE_CONCATENATION_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_expression.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Concatenation;

/***************************************************************************/

struct MultipleConcatenation
	:	public Expression
{

/***************************************************************************/

	virtual Concatenation const & getConcatenation() const = 0;
	
	virtual Expression const & getRepeatExpression() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_MULTIPLE_CONCATENATION_HPP__
