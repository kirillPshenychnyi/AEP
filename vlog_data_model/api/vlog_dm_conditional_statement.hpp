#ifndef __VLOG_DM_CONDITIONAL_STATEMENT_HPP__
#define __VLOG_DM_CONDITIONAL_STATEMENT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_statement.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct ConditionalBranch;

/***************************************************************************/

struct ConditionalStatement
	:	public Statement
{

/***************************************************************************/

	virtual int getBranchesCount() const = 0;

	virtual ConditionalBranch const & getBranch( int _idx ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONDITIONAL_STATEMENT_HPP__
