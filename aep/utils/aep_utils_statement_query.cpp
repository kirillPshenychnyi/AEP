#include "stdafx.h"

#include "aep\utils\aep_utils_statement_query.hpp"

#include "vlog_data_model\api\vlog_dm_statement_cast.hpp"
#include "vlog_data_model\api\vlog_dm_sequential_block.hpp"
#include "vlog_data_model\api\vlog_dm_case_statement.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_statement.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_branch.hpp"
#include "vlog_data_model\api\vlog_dm_for_loop.hpp"
#include "vlog_data_model\api\vlog_dm_forever_loop.hpp"
#include "vlog_data_model\api\vlog_dm_while_loop.hpp"
#include "vlog_data_model\api\vlog_dm_repeat_loop.hpp"
#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_case_item.hpp"
#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

template< typename _TTarget >
StatementQuery< _TTarget >::StatementQuery( 
		VlogDM::BehavioralProcess const & _process 
	,	ConstructCallback && _callback
	,	ConstructPredicate && _predicate
	)
	:	BaseClass( 
				std::forward< ConstructCallback >( _callback )
			,	std::forward< ConstructPredicate >( _predicate ) 
		)
	,	m_process( _process )
{
}

/***************************************************************************/

template< typename _TTarget >
void
StatementQuery< _TTarget >::query()
{
	m_process.getStatement().accept( *this );
}

/***************************************************************************/

template< typename _TTarget >
void 
StatementQuery< _TTarget >::visit( VlogDM::SequentialBlock const & _block )
{	
	processAsConstructsContainer< Query, VlogDM::Statement >( 
			_block.getStatementsCount()
		,	[ & ]( int _idx ) -> VlogDM::Statement const &
			{
				return _block.getStatement( _idx );
			}
		,	*this
	);
}

/***************************************************************************/

template< typename _TTarget >
void 
StatementQuery< _TTarget >::visit( VlogDM::CaseStatement const & _case )
{
	processAsTargetConstruct( _case );

	processAsConstructsContainer< Query, VlogDM::Statement >( 
			_case.getItemsCount()
		,	[ & ]( int _idx ) -> VlogDM::Statement const &
			{	
				return _case.getItem( _idx ).getStatement();
			}
		,	*this
	);
}

/***************************************************************************/

template<typename _TTarget>
void 
StatementQuery< _TTarget >::visit( VlogDM::ForLoop const & _for )
{
	processLoop( _for );
}

/***************************************************************************/

template< typename _TTarget >
void 
StatementQuery< _TTarget >::visit( VlogDM::WhileLoop const & _while )
{
	processLoop( _while );
}

/***************************************************************************/

template< typename _TTarget >
void 
StatementQuery< _TTarget >::visit( VlogDM::ForeverLoop const & _forever )
{
	processLoop( _forever );
}

/***************************************************************************/

template< typename _TTarget >
void 
StatementQuery< _TTarget >::visit( VlogDM::RepeatLoop const & _repeat )
{
	processLoop( _repeat );
}

/***************************************************************************/

template< typename _TTarget >
void
StatementQuery< _TTarget >::visit( VlogDM::ConditionalStatement const & _statement )
{
	processAsTargetConstruct( _statement );

	processAsConstructsContainer< Query, VlogDM::Statement >( 
			_statement.getBranchesCount()
		,	[ & ]( int _idx ) -> VlogDM::Statement const &
			{
				return _statement.getBranch( _idx ).getStatement();
			}
		,	*this
	);
}

/***************************************************************************/

template< typename _TTarget >
void 
StatementQuery< _TTarget >::visit( VlogDM::BlockingAssignment const & _assignment )
{
	processAsTargetConstruct( _assignment );
}

/***************************************************************************/

template< typename _TTarget >
template< typename _TLoop >
void 
StatementQuery< _TTarget >::processLoop( const _TLoop & _loop )
{
	processAsTargetConstruct( _loop );
	_loop.getLoopStatement().accept( *this );
}

/***************************************************************************/

template class StatementQuery< VlogDM::CaseStatement >;
template class StatementQuery< VlogDM::BlockingAssignment >;
template class StatementQuery< VlogDM::ConditionalStatement >;

/***************************************************************************/

}
}

/***************************************************************************/