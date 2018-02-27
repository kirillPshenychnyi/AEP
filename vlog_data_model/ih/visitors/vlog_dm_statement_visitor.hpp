#ifndef __VLOG_DM_STATEMENT_VISITOR_HPP__
#define __VLOG_DM_STATEMENT_VISITOR_HPP__

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct ConditionalStatement;
struct BlockingAssignment;

/***************************************************************************/

struct StatementVisitor
{

/***************************************************************************/

	virtual void visit( ConditionalStatement const & _statement ) = 0;

	virtual void visit( BlockingAssignment const & _assignment ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_VISITOR_HPP__
