#ifndef __AEP_UTILS_STATEMENT_QUERY_HPP__
#define __AEP_UTILS_STATEMENT_QUERY_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"

#include <functional>

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

template< typename _TTarget >
class StatementQuery
	:	public VlogDM::StatementVisitor
{

/***************************************************************************/

	using StatementCallback = std::function< void( _TTarget const & ) >;
	using StatementRetriever = std::function< VlogDM::Statement const & ( int ) >;

/***************************************************************************/

public:

/***************************************************************************/

	StatementQuery( 
			VlogDM::BehavioralProcess const & _process
		,	StatementCallback && _callback
	);

/***************************************************************************/

	void query();

/***************************************************************************/

private:

/***************************************************************************/

	void visit( VlogDM::SequentialBlock const & _block ) final;

	void visit( VlogDM::CaseStatement const & _case ) final;

	void visit( VlogDM::ConditionalStatement const & _statement ) final;

	void visit( VlogDM::BlockingAssignment const & _assignment ) final;

/***************************************************************************/

	template< typename _TSeqStatement >
	void processAsTopStatement( _TSeqStatement const & _statement );

	template< typename _TSeqStatement >
	void processAsStatementsContainer( 
			_TSeqStatement const & _statement
		,	int _statements
		,	StatementRetriever _retriever
	);

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::BehavioralProcess const & m_process;

	StatementCallback m_callback;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__AEP_UTILS_STATEMENT_QUERY_HPP__
