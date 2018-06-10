#ifndef __AEP_UTILS_EXPRESSION_EXTRACTOR_HPP__
#define __AEP_UTILS_EXPRESSION_EXTRACTOR_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

class ConditionHolder;

/***************************************************************************/

class ExpressionExtractor
	:	public VlogDM::StatementVisitor
{

/***************************************************************************/

	using CallBack = std::function< void( VlogDM::Expression const& ) >;

/***************************************************************************/

public:

/***************************************************************************/

	ExpressionExtractor( 
			CallBack && _callback
		,	ConditionHolder & _collector
	);

/***************************************************************************/

private:

/***************************************************************************/

	void visit( VlogDM::SequentialBlock const & _block ) final;

	void visit( VlogDM::CaseStatement const & _case ) final;

	void visit( VlogDM::ForLoop const & _for ) final;

	void visit( VlogDM::WhileLoop const & _while ) final;

	void visit( VlogDM::ForeverLoop const & _forever ) final;

	void visit( VlogDM::RepeatLoop const & _repeat ) final;

	void visit( VlogDM::ConditionalStatement const & _condition ) final;

	void visit( VlogDM::BlockingAssignment const & _assignment ) final;

/***************************************************************************/

private:

/***************************************************************************/

	CallBack m_callback;

	ConditionHolder & m_collector;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__AEP_UTILS_EXPRESSION_EXTRACTOR_HPP__
