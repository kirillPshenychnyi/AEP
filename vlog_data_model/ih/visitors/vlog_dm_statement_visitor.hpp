#ifndef __VLOG_DM_STATEMENT_VISITOR_HPP__
#define __VLOG_DM_STATEMENT_VISITOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct ConditionalStatement;
struct BlockingAssignment;
struct SequentialBlock;
struct CaseStatement;

/***************************************************************************/

struct StatementVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( ConditionalStatement const & _statement ) = 0;

	virtual void visit( BlockingAssignment const & _assignment ) = 0;
	
	virtual void visit( SequentialBlock const & _assignment ) = 0;

	virtual void visit( CaseStatement const & _case ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_VISITOR_HPP__
