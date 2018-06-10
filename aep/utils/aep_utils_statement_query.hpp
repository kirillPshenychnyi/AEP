#ifndef __AEP_UTILS_STATEMENT_QUERY_HPP__
#define __AEP_UTILS_STATEMENT_QUERY_HPP__

/***************************************************************************/

#include "aep\utils\aep_utils_base_query.hpp"

#include "vlog_data_model\api\vlog_dm_statement_cast.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

template< typename _TTarget >
class StatementQuery
	:	public BaseQuery< _TTarget, VlogDM::StatementCast >
	,	public VlogDM::StatementVisitor
{

/***************************************************************************/

	using BaseClass = BaseQuery< _TTarget, VlogDM::StatementCast >;
	using Query = StatementQuery< _TTarget >;

/***************************************************************************/

public:

/***************************************************************************/

	StatementQuery( 
			ConstructCallback && _callback
		,	ConstructPredicate && _predicate
	);

/***************************************************************************/

	void query( VlogDM::BehavioralProcess const & _process );

/***************************************************************************/

private:

/***************************************************************************/

	void visit( VlogDM::SequentialBlock const & _block ) final;

	void visit( VlogDM::CaseStatement const & _case ) final;

	void visit( VlogDM::ForLoop const & _for ) final;

	void visit( VlogDM::WhileLoop const & _while ) final;

	void visit( VlogDM::ForeverLoop const & _forever ) final;

	void visit( VlogDM::RepeatLoop const & _repeat ) final;

	void visit( VlogDM::ConditionalStatement const & _statement ) final;

	void visit( VlogDM::BlockingAssignment const & _assignment ) final;

/***************************************************************************/

	template< typename _TLoop >
	void processLoop( const _TLoop& _loop );

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__AEP_UTILS_STATEMENT_QUERY_HPP__
