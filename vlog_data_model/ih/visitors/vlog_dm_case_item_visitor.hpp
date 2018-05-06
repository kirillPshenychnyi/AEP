#ifndef __VLOG_DM_CASE_ITEM_VISITOR_HPP__
#define __VLOG_DM_CASE_ITEM_VISITOR_HPP__

/***************************************************************************/

#include "common_tools\utils\declare_visitors.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct CaseItem;
struct DefaultCaseItem;

/***************************************************************************/

DECLARE_VISITORS( CaseItem, CaseItem, DefaultCaseItem )

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_ITEM_VISITOR_HPP__
