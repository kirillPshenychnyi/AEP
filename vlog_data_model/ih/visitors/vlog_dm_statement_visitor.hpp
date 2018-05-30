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
struct ForLoop;
struct WhileLoop;
struct RepeatLoop;
struct ForeverLoop;
struct ConditionalLoop;

/***************************************************************************/

DECLARE_VISITORS( 
		Statement
	,	ConditionalStatement
	,	BlockingAssignment
	,	SequentialBlock
	,	CaseStatement 
	,	ForLoop
	,	WhileLoop
	,	RepeatLoop
	,	ForeverLoop
)

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_VISITOR_HPP__
