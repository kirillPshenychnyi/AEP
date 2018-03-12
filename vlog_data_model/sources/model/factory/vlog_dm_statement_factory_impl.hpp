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
		std::unique_ptr< BinaryOperator > _assignment
	) const override;

	Writable::ConditionalStatementPtr newConditionalStatement(
		Location const & _location 
	) const override;

	ConditionalBranchPtr newConditionalBranch(
			ExpressionPtr _expression
		,	StatementPtr _statement
	) const override;

	std::unique_ptr< Writable::SequentialBlock > newSequentialBlock(
		Location const & _location
	) const override;

	Writable::CaseStatementPtr newCaseStatement(
			Location const & _location 
		,	ExpressionPtr _expression
	) const override;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_FACTORY_IMPL_HPP__
