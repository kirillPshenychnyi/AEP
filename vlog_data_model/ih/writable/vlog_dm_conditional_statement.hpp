#ifndef __VLOG_DM_WRITABLE_CONDITIONAL_STATEMENT_HPP__
#define __VLOG_DM_WRITABLE_CONDITIONAL_STATEMENT_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_conditional_statement.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

template < typename _TBase, typename _TBranch >
struct BaseConditionalStatement
	:	public _TBase
{

/***************************************************************************/

	typedef
		std::unique_ptr< _TBranch >
		Branch;

/***************************************************************************/

	virtual void addBranch( Branch _branch ) = 0;

/***************************************************************************/

};

/***************************************************************************/

class ConditionalStatement
	:	public BaseConditionalStatement< VlogDM::ConditionalStatement, ConditionalBranch > 
{
};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_WRITABLE_CONDITIONAL_STATEMENT_HPP__
