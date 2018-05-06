#ifndef __VLOG_DM_DECLARATION_VISITOR_HPP__
#define __VLOG_DM_DECLARATION_VISITOR_HPP__

/***************************************************************************/

#include "common_tools\utils\declare_visitors.hpp"

/***************************************************************************/

namespace VlogDM{

/***************************************************************************/

struct PortDeclaration;
struct VariableDeclaration;

/***************************************************************************/

DECLARE_VISITORS( Declaration, PortDeclaration, VariableDeclaration )

/***************************************************************************/

}

/***************************************************************************/

#endif // __VLOG_DM_DECLARATION_VISITOR_HPP__