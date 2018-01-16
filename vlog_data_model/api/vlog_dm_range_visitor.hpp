#ifndef __VLOG_DM_RANGE_VISITOR_HPP__
#define __VLOG_DM_RANGE_VISITOR_HPP__

/***************************************************************************/

#include "boost\noncopyable.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct ExpressionRange;
	struct PartSelectRange;

/***************************************************************************/

struct RangeVisitor
	:	public boost::noncopyble
{

/***************************************************************************/

	virtual ~RangeVisitor(){}

	virtual void visit( ExpressionRange const & _range ) = 0;

	virtual void visit( PartSelectRange const & _range ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_RANGE_VISITOR_HPP__
