#ifndef __VLOG_DM_STATEMENT_FACTORY_IMPL_HPP__
#define __VLOG_DM_STATEMENT_FACTORY_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_statement_factory.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class StatementFactoryImpl
	:	public Writable::StatementFactory
{

/***************************************************************************/

	std::unique_ptr< BlockingAssignment > newBlockingAssignment(
			Location const & _location 
		,	std::unique_ptr< BinaryOperator > _assignment
	) const override;

	Writable::ConditionalStatementPtr newConditionalStatement(
		Location const & _location 
	) const override;

	ConditionalBranchPtr newConditionalBranch(
			ExpressionPtr _expression
		,	StatementPtr _statement
		,	Location const & _location
	) const override;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_FACTORY_IMPL_HPP__
