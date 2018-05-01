#ifndef __VLOG_DM_CASE_ITEM_CAST_HPP__
#define __VLOG_DM_CASE_ITEM_CAST_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\visitors\vlog_dm_case_item_visitor.hpp"
#include "vlog_data_model\api\vlog_dm_base_case_item.hpp"

#include "common_tools\utils\visitor_cast.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

template < typename _TTarget >
struct CaseItemCast
	:	public Tools::Cast< _TTarget, BaseCaseItem, CaseItemDefaultVisitor >
{
};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_ITEM_CAST_HPP__
