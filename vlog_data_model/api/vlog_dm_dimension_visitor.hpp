#ifndef __VLOG_DM_DIMENSION_VISITOR_HPP__
#define __VLOG_DM_DIMENSION_VISITOR_HPP__

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct PackedDimension;
	struct UnpackedDimension;

/***************************************************************************/

struct DimensionVisitor
{

/***************************************************************************/

	virtual ~DimensionVisitor() {}
	
	virtual void visit( PackedDimension const & _dimension ) const = 0;

	virtual void visit( UnpackedDimension const & _dimension ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DIMENSION_VISITOR_HPP__
