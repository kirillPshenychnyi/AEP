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

	void visit( ConditionalStatement const & _statement ) override;

	void visit( BlockingAssignment const & _assignment ) override;

	void visit( SequentialBlock const & _block ) override;

	void visit( CaseStatement const & _case ) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_REGENERATOR_HPP__
