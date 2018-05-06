#ifndef __VLOG_DM_STATEMENT_VISITOR_HPP__
#define __VLOG_DM_STATEMENT_VISITOR_HPP__

/***************************************************************************/

#include "common_tools\utils\declare_visitors.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct ConditionalStatement;
struct BlockingAssignment;
struct SequentialBlock;
struct CaseStatement;

/***************************************************************************/

DECLARE_VISITORS( 
		Statement
	,	ConditionalStatement
	,	BlockingAssignment
	,	SequentialBlock
	,	CaseStatement 
)

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_VISITOR_HPP__
