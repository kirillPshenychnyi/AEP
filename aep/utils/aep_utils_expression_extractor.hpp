#ifndef __AEP_UTILS_EXPRESSION_EXTRACTOR_HPP__
#define __AEP_UTILS_EXPRESSION_EXTRACTOR_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

class ExpressionExtractor
	:	public VlogDM::StatementVisitor
{

/***************************************************************************/

public:

/***************************************************************************/

	void forEachExpression(
		std::function< void ( VlogDM::Expression const & ) > _callback 
	) const;

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

	std::vector< const VlogDM::Expression * > m_expressions;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__AEP_UTILS_EXPRESSION_EXTRACTOR_HPP__
