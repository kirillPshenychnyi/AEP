#ifndef __VLOG_DM_WRITABLE_CASE_ITEM_HPP__
#define __VLOG_DM_WRITABLE_CASE_ITEM_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_case_item.hpp"
#include "vlog_data_model\api\vlog_dm_default_case_item.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

template< typename _TBase >
struct BaseCaseItem
	:	public _TBase
{

/***************************************************************************/

	virtual void setStatement( StatementPtr _statement ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct CaseItem
	:	BaseCaseItem< VlogDM::CaseItem >
{

/***************************************************************************/

	virtual void addExpression( ExpressionPtr _expression ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct DefaultCaseItem
	:	BaseCaseItem< VlogDM::DefaultCaseItem >
{
};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_WRITABLE_CASE_ITEM_HPP__
