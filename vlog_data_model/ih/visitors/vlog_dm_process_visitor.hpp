#ifndef __VLOG_DM_PROCESS_VISITOR_HPP__
#define __VLOG_DM_PROCESS_VISITOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct ContinuousAssignment;
struct BehavioralProcess;

/***************************************************************************/

struct ProcessVisitor
	:	boost::noncopyable
{

/***************************************************************************/

	virtual void visit( ContinuousAssignment const & _assign ) = 0;

	virtual void visit( BehavioralProcess const & _assign ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_PROCESS_VISITOR_HPP__
