#ifndef __VLOG_DM_STATEMENT_FACTORY_HPP__
#define __VLOG_DM_STATEMENT_FACTORY_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM {
namespace Writable { 

/***************************************************************************/

struct StatementFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual std::unique_ptr< BlockingAssignment > newBlockingAssignment(
			Location const & _location 
		,	std::unique_ptr< BinaryOperator > _assignment
	) const = 0;

	virtual ConditionalStatementPtr newConditionalStatement(
		Location const & _location 
	) const = 0 ;

	virtual ConditionalBranchPtr newConditionalBranch(
				ExpressionPtr _expression
			,	StatementPtr _statement
			,	Location const & _location
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_FACTORY_HPP__
