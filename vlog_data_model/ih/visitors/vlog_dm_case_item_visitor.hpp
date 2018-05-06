#ifndef __VLOG_DM_CASE_ITEM_VISITOR_HPP__
#define __VLOG_DM_CASE_ITEM_VISITOR_HPP__

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct CaseItem;
struct DefaultCaseItem;

/***************************************************************************/

struct CaseItemVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( CaseItem const & _caseItem ) = 0;

	virtual void visit( DefaultCaseItem const & _caseItem ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct CaseItemDefaultVisitor
	:	public CaseItemVisitor
{

/***************************************************************************/

	void visit( CaseItem const & _caseItem ) override {}

	void visit( DefaultCaseItem const & _caseItem ) override {}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_ITEM_VISITOR_HPP__
