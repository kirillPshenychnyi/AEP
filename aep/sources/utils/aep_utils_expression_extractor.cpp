#include "stdafx.h"

#include "aep\sources\utils\aep_utils_expression_extractor.hpp"
#include "aep\sources\utils\aep_utils_condition_holder.hpp"

#include "vlog_data_model\api\vlog_dm_statement_cast.hpp"
#include "vlog_data_model\api\vlog_dm_sequential_block.hpp"
#include "vlog_data_model\api\vlog_dm_case_statement.hpp"
#include "vlog_data_model\api\vlog_dm_case_item.hpp"
#include "vlog_data_model\api\vlog_dm_default_case_item.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_statement.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_branch.hpp"
#include "vlog_data_model\api\vlog_dm_for_loop.hpp"
#include "vlog_data_model\api\vlog_dm_forever_loop.hpp"
#include "vlog_data_model\api\vlog_dm_while_loop.hpp"
#include "vlog_data_model\api\vlog_dm_case_item_cast.hpp"
#include "vlog_data_model\api\vlog_dm_repeat_loop.hpp"
#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

ExpressionExtractor::ExpressionExtractor( 
		CallBack && _callback
	,	ConditionHolder & _collector
)
	:	m_callback( _callback )
	,	m_collector( _collector )
{
}

/***************************************************************************/

void
ExpressionExtractor::visit( VlogDM::SequentialBlock const & _block )
{
	const int nStmts = _block.getStatementsCount();

	for( int i = 0; i < nStmts; ++i )
		_block.getStatement( i ).accept( *this );
}

/***************************************************************************/

void
ExpressionExtractor::visit( VlogDM::CaseStatement const & _case )
{
	const int nBranches = _case.getItemsCount();

	VlogDM::CaseItemCast< VlogDM::CaseItem > itemCaster;

	for( int i = 0; i < nBranches; ++i )
	{
		VlogDM::BaseCaseItem const & caseItem = _case.getItem( i );
	
		m_collector.pushCondition( _case, i );

		if( auto castRes = itemCaster.cast( caseItem ) )
		{
			const int nExpressions = castRes->getExpressionsCount();
			
			for( int j = 0; j < nExpressions; ++j )
				m_callback( castRes->getExpression( j ) );
		}

		caseItem.getStatement().accept( *this );

		m_collector.popCondition();
	}
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::ForLoop const & _for )
{
	m_collector.pushCondition( _for, 0 );
	m_callback( _for.getInitialization() );
	m_callback( _for.getCondition() );
	m_callback( _for.getIteration() );
	m_collector.popCondition();
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::WhileLoop const & _while )
{
	m_collector.pushCondition( _while, 0 );
	m_callback( _while.getCondition() );
	m_collector.popCondition();

	_while.getLoopStatement().accept( *this );
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::ForeverLoop const & _forever )
{
	_forever.getLoopStatement().accept( *this );
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::RepeatLoop const & _repeat )
{
	m_collector.pushCondition( _repeat, 0 );
	m_callback( _repeat.getCondition() );
	m_collector.popCondition();

	_repeat.getLoopStatement().accept( *this );
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::ConditionalStatement const & _conditional )
{
	const int nBranches = _conditional.getBranchesCount();

	for( int i = 0; i < nBranches; ++i )
	{
		m_collector.pushCondition( _conditional, i );
		_conditional.getBranch( i ).getStatement().accept( *this );
		m_collector.popCondition();
	}
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::BlockingAssignment const & _assignment )
{
	m_callback( _assignment.getAssignment() );
}

/***************************************************************************/

}
}