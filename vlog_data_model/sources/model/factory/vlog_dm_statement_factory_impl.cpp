#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_statement_factory_impl.hpp"

#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"

#include "vlog_data_model\sources\model\vlog_dm_conditional_statement_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_conditional_branch_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_blocking_assignment_impl.hpp"

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

}
