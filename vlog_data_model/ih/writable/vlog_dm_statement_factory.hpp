#ifndef __VLOG_DM_STATEMENT_FACTORY_HPP__
#define __VLOG_DM_STATEMENT_FACTORY_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_case_kind.hpp"

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
		std::unique_ptr< BinaryOperator > _assignment
	) const = 0;

	virtual ConditionalStatementPtr newConditionalStatement(
		Location const & _location 
	) const = 0 ;

	virtual ConditionalBranchPtr newConditionalBranch(
				ExpressionPtr _expression
			,	StatementPtr _statement
	) const = 0;

	virtual std::unique_ptr< SequentialBlock > newSequentialBlock(
		Location const & _location 
	) const = 0;

	virtual CaseStatementPtr newCaseStatement(
			Location const & _location 
		,	ExpressionPtr _expression
		,	CaseKind::Kind _kind
		,	bool _isParallelCase
		,	bool _isFullCase
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_FACTORY_HPP__
