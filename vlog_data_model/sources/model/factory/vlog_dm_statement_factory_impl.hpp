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
	) const final;

	Writable::ConditionalStatementPtr newConditionalStatement(
		Location const & _location 
	) const final;

	ConditionalBranchPtr newConditionalBranch(
			ExpressionPtr _expression
		,	StatementPtr _statement
	) const override;

	std::unique_ptr< Writable::SequentialBlock > newSequentialBlock(
		Location const & _location
	) const final;

	Writable::CaseStatementPtr newCaseStatement(
			Location const & _location 
		,	ExpressionPtr _expression
		,	CaseKind::Kind _kind
		,	bool _isParallelCase
		,	bool _isFullCase
	) const final;

	WhileLoopPtr newWhileLoop(
			Location const & _location
		,	ExpressionPtr _condition
		,	StatementPtr _loopStmt
	) const final;

	RepeatLoopPtr newRepeatLoop(
			Location const & _location
		,	ExpressionPtr _condition
		,	StatementPtr _loopStmt
	) const final;

	ForLoopPtr newForLoop(
			Location const & _location
		,	BinaryOperatorPtr _initialization
		,	ExpressionPtr _condition
		,	BinaryOperatorPtr _iteration
		,	StatementPtr _loopStmt
	) const final;

	ForeverLoopPtr newForeverLoop(
			Location const & _location
		,	StatementPtr _loopStmt
	) const final;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_FACTORY_IMPL_HPP__
