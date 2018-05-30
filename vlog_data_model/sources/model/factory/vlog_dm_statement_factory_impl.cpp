#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_statement_factory_impl.hpp"

#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"

#include "vlog_data_model\sources\model\vlog_dm_conditional_statement_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_conditional_branch_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_blocking_assignment_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_sequential_block_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_case_statement_impl.hpp"

#include "vlog_data_model\sources\model\vlog_dm_for_loop_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_repeat_loop_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_while_loop_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_forever_loop_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

std::unique_ptr< BlockingAssignment > 
StatementFactoryImpl::newBlockingAssignment( 
	std::unique_ptr< BinaryOperator > _assignment 
) const
{
	return std::make_unique< BlockingAssignmentImpl >( std::move( _assignment ) );
}

/***************************************************************************/

Writable::ConditionalStatementPtr
StatementFactoryImpl::newConditionalStatement( Location const & _location ) const
{
	return std::make_unique< ConditionalStatementImpl >( _location );
}

/***************************************************************************/

ConditionalBranchPtr 
StatementFactoryImpl::newConditionalBranch(
		ExpressionPtr _expression
	,	StatementPtr _statement
) const
{
	return 
		std::make_unique< ConditionalBranchImpl >( 
				std::move( _expression )
			,	std::move( _statement )
		);
}

/***************************************************************************/

std::unique_ptr< Writable::SequentialBlock > 
StatementFactoryImpl::newSequentialBlock( Location const & _location ) const
{
	return std::make_unique< SequentialBlockImpl >( _location );
}

/***************************************************************************/

Writable::CaseStatementPtr 
StatementFactoryImpl::newCaseStatement( 
		Location const & _location
	,	ExpressionPtr _expression 
	,	CaseKind::Kind _kind
	,	bool _isParallelCase
	,	bool _isFullCase
) const
{
	return 
		std::make_unique< CaseStatementImpl >( 
				_location
			,	std::move( _expression )
			,	_kind
			,	_isParallelCase
			,	_isFullCase
		) ;
}

/***************************************************************************/

WhileLoopPtr
StatementFactoryImpl::newWhileLoop( 
		Location const & _location
	,	ExpressionPtr _condition
	,	StatementPtr _loopStmt 
) const
{
	return 
		std::make_unique< WhileLoopImpl >( 
				_location
			,	std::move( _loopStmt ) 
			,	std::move( _condition )
		);
}

/***************************************************************************/

RepeatLoopPtr 
StatementFactoryImpl::newRepeatLoop( 
		Location const & _location
	,	ExpressionPtr _condition
	,	StatementPtr _loopStmt 
) const
{
	return 
		std::make_unique< RepeatLoopImpl >( 
				_location
			,	std::move( _loopStmt ) 
			,	std::move( _condition )
		);
}

/***************************************************************************/

ForLoopPtr
StatementFactoryImpl::newForLoop( 
		Location const & _location
	,	BinaryOperatorPtr _initialization
	,	ExpressionPtr _condition
	,	BinaryOperatorPtr _iteration
	,	StatementPtr _loopStmt 
) const
{
	return 
		std::make_unique< ForLoopImpl >( 
				_location
			,	std::move( _loopStmt ) 
			,	std::move( _initialization )
			,	std::move( _condition )
			,	std::move( _iteration )
		);
}

/***************************************************************************/

ForeverLoopPtr 
StatementFactoryImpl::newForeverLoop( 
		Location const & _location
	,	StatementPtr _loopStmt 
) const
{
	return std::make_unique< ForeverLoopImpl >( _location, std::move( _loopStmt ) );
}

/***************************************************************************/

}
