#include "stdafx.h"

#include "aep\utils\aep_utils_expression_extractor.hpp"

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

void 
ExpressionExtractor::forEachExpression( 
	std::function< void ( VlogDM::Expression const& ) > _callback 
) const
{
	for( auto expression : m_expressions )
		_callback( *expression );
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
	
		if( auto castRes = itemCaster.cast( caseItem ) )
		{
			const int nExpressions = castRes->getExpressionsCount();

			for( int j = 0; j < nExpressions; ++j )
				m_expressions.push_back( &castRes->getExpression( i ) );
		}

		caseItem.getStatement().accept( *this );
	}
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::ForLoop const & _for )
{
	m_expressions.push_back( &_for.getInitialization() );
	m_expressions.push_back( &_for.getCondition() );
	m_expressions.push_back( &_for.getIteration() );
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::WhileLoop const & _while )
{
	m_expressions.push_back( &_while.getCondition() );
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
	m_expressions.push_back( &_repeat.getCondition() );
	_repeat.getLoopStatement().accept( *this );
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::ConditionalStatement const & _conditional )
{
	const int nBranches = _conditional.getBranchesCount();

	for( int i = 0; i < nBranches; ++i )
		_conditional.getBranch( i ).getStatement().accept( *this );
}

/***************************************************************************/

void 
ExpressionExtractor::visit( VlogDM::BlockingAssignment const & _assignment )
{
	m_expressions.push_back( &_assignment.getAssignment() );
}

/***************************************************************************/

}
}