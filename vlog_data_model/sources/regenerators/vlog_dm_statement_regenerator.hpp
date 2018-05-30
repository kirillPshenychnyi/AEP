#ifndef __VLOG_DM_STATEMENT_REGENERATOR_HPP__
#define __VLOG_DM_STATEMENT_REGENERATOR_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\regenerators\vlog_dm_base_regenerator.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators {

/***************************************************************************/

class StatementRegenerator
	:	public StatementVisitor
	,	public BaseRegenerator
{

/***************************************************************************/

public:

/***************************************************************************/

	StatementRegenerator( std::ostream & _target );

/***************************************************************************/

private:

/***************************************************************************/

	void visit( ConditionalStatement const & _statement ) final;

	void visit( BlockingAssignment const & _assignment ) final;

	void visit( SequentialBlock const & _block ) final;

	void visit( CaseStatement const & _case ) final;

	void visit( ForLoop const & _forLoop ) final;

	void visit( RepeatLoop const & _repeatLoop ) final;

	void visit( WhileLoop const & _whileLoop ) final;

	void visit( ForeverLoop const & _foreverLoop ) final;

/***************************************************************************/

	void regenerateConditionalLoop(
			ConditionalLoop const & _loop 
		,	std::string const & _kind
	);

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_REGENERATOR_HPP__
