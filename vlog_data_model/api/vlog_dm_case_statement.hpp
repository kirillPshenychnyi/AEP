#ifndef __VLOG_DM_CASE_STATEMENT_HPP__
#define __VLOG_DM_CASE_STATEMENT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_statement.hpp"
#include "vlog_data_model\api\vlog_dm_case_kind.hpp"

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

	virtual bool isParallelCase() const = 0;

	virtual bool isFullCase() const = 0;

	virtual CaseKind::Kind getCaseKind() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_STATEMENT_HPP__
