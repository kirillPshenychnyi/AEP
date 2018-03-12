#ifndef __VLOG_DM_CASE_STATEMENT_HPP__
#define __VLOG_DM_CASE_STATEMENT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_statement.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Expression;
struct BaseCaseItem;

/***************************************************************************/

struct CaseStatement
	:	public Statement
{

/***************************************************************************/

	virtual Expression const & getCaseExpression() const = 0;

	virtual int getItemsCount() const = 0;

	virtual BaseCaseItem const & getItem( int _idx ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_STATEMENT_HPP__
