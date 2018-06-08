#ifndef __AEP_UTILS_BASE_QUERY_HPP__
#define __AEP_UTILS_BASE_QUERY_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

template< typename _TTarget, template < typename > typename _Caster >
class BaseQuery
{

/***************************************************************************/

protected:

/***************************************************************************/

	using ConstructCallback = std::function< void ( _TTarget const & ) >;
	using ConstructPredicate = std::function< bool ( _TTarget const & ) >;

	template< typename _TConstruct >
	using StatementRetriever = std::function< _TConstruct const & ( int ) >;
	
/***************************************************************************/

protected:

/***************************************************************************/

	BaseQuery(
			ConstructCallback && _callback
		,	ConstructPredicate && _predicate = [ ]( _TTarget const & ) { return true; }
	)
		:	m_callback( _callback )
		,	m_predicate( _predicate )
	{
	}

	template< typename _TQuery, typename _TConstruct >
	void processAsConstructsContainer( 
			int _statements
		,	StatementRetriever< _TConstruct > _retriever
		,	_TQuery & _query
	)
	{
		for( int i = 0; i < _statements; ++i )
			_retriever( i ).accept( _query );
	}

	template< typename _TConstruct >
	void processAsTargetConstruct( _TConstruct const & _construct )
	{
		_Caster< _TTarget > caster;

		if( auto castRes = caster.cast( _construct ) )
		{
			if( m_predicate( *castRes ) )
				m_callback( *castRes );
		}
	}

/***************************************************************************/

	ConstructCallback m_callback;

	ConstructPredicate m_predicate;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__AEP_UTILS_BASE_QUERY_HPP__
