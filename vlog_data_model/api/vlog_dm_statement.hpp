#ifndef __VLOG_DM_STATEMENT_HPP__
#define __VLOG_DM_STATEMENT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_located.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct StatementVisitor;

/***************************************************************************/

struct Statement
	:	public Located
{

/***************************************************************************/

	virtual void accept( StatementVisitor & _visitor ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_HPP__
