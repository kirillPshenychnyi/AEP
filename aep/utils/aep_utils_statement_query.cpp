#include "stdafx.h"

#include "aep\utils\aep_utils_statement_query.hpp"

#include "vlog_data_model\api\vlog_dm_statement_cast.hpp"
#include "vlog_data_model\api\vlog_dm_sequential_block.hpp"
#include "vlog_data_model\api\vlog_dm_case_statement.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_statement.hpp"
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
	,	StatementCallback && _callback
	)
	:	m_process( _process )
	,	m_callback( _callback )
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

}

/***************************************************************************/

template< typename _TTarget >
void 
StatementQuery< _TTarget >::visit( VlogDM::CaseStatement const & _case )
{
	processAsTopStatement( _case );

	processAsStatementsContainer( 
			_case
		,	_case.getItemsCount()
		,	[ & ]( int _idx ) -> VlogDM::Statement const &
			{
				return _case.getItem( _idx ).getStatement();
			}
	);
}

/***************************************************************************/

template< typename _TTarget >
void
StatementQuery< _TTarget >::visit( VlogDM::ConditionalStatement const & _statement )
{
	processAsTopStatement( _statement );
}

/***************************************************************************/

template< typename _TTarget >
void 
StatementQuery< _TTarget >::visit( VlogDM::BlockingAssignment const & _assignment )
{
	processAsTopStatement( _assignment );
}

/***************************************************************************/

template< typename _TTarget >
template< typename _TSeqStatement >
void 
StatementQuery< _TTarget >::processAsTopStatement( 
		_TSeqStatement const & _statement 
)
{
	using namespace VlogDM;

	StatementCast< _TTarget > caster;

	if( auto castRes = caster.cast( _statement ) )
		m_callback( *castRes );
}

/***************************************************************************/

template< typename _TTarget >
template< typename _TSeqStatement >
void 
StatementQuery< _TTarget >::processAsStatementsContainer(
		_TSeqStatement const & _statement
	,	int _statements
	,	StatementRetriever _retriever
)
{
	for( int i = 0; i < _statements; ++i )
		_retriever( i ).accept( *this );
}

/***************************************************************************/

template class StatementQuery< VlogDM::CaseStatement >;
template class StatementQuery< VlogDM::BlockingAssignment >;
template class StatementQuery< VlogDM::ConditionalStatement >;

/***************************************************************************/

}
}

/***************************************************************************/