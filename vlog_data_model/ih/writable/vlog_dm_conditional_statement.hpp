#ifndef __VLOG_DM_WRITABLE_CONDITIONAL_STATEMENT_HPP__
#define __VLOG_DM_WRITABLE_CONDITIONAL_STATEMENT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_conditional_statement.hpp"
#include "vlog_data_model\api\vlog_dm_case_statement.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

template < typename _TBase, typename _TBranch >
struct BaseBranchStatement
	:	public _TBase
{

/***************************************************************************/

	typedef
		std::unique_ptr< _TBranch >
		Branch;

/***************************************************************************/

	virtual ~BaseBranchStatement() = default;

	virtual void addBranch( Branch _branch ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct ConditionalStatement
	:	public BaseBranchStatement< VlogDM::ConditionalStatement, ConditionalBranch > 
{
};

/***************************************************************************/

struct CaseStatement
	:	public BaseBranchStatement< VlogDM::CaseStatement, VlogDM::BaseCaseItem > 
{
};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_WRITABLE_CONDITIONAL_STATEMENT_HPP__
