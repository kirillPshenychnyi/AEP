#ifndef __VLOG_DM_CONDITIONAL_BRANCH_HPP__
#define __VLOG_DM_CONDITIONAL_BRANCH_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_located.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Location;
struct Statement;

/***************************************************************************/

struct ConditionalBranch
	:	public Located
{

/***************************************************************************/

	virtual boost::optional< Expression const & > getCondition () const = 0;

	virtual Statement const & getStatement() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONDITIONAL_BRANCH_HPP__

