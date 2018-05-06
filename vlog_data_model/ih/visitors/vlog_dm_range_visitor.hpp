#ifndef __VLOG_DM_RANGE_VISITOR_HPP__
#define __VLOG_DM_RANGE_VISITOR_HPP__

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct Range;
	struct ExpressionRange;
	struct PartSelectRange;
	struct MultidimensionalRange;

/***************************************************************************/

struct RangeVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( ExpressionRange const & _range ) = 0;

	virtual void visit( PartSelectRange const & _range ) = 0;

	virtual void visit( MultidimensionalRange const & _range ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct RangeDefaultVisitor
	:	public RangeVisitor
{

/***************************************************************************/

	void visit( ExpressionRange const & _range ) override {}

	void visit( PartSelectRange const & _range ) override {}

	void visit( MultidimensionalRange const & _range ) override {}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_RANGE_VISITOR_HPP__
