#ifndef __VLOG_DM_EXPRESSION_HPP__
#define __VLOG_DM_EXPRESSION_HPP__

/***************************************************************************/

#include "api\vlog_dm_located.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct ExpressionVisitor;

/***************************************************************************/

struct Expression
	:	public Located
{

/***************************************************************************/

	virtual ~Expression() {}

	virtual void accept( ExpressionVisitor & _visitor ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // __VLOG_DM_EXPRESSION_HPP__