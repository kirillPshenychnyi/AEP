#ifndef __VLOG_DM_ITEMS_FACTORY_HPP__
#define __VLOG_DM_ITEMS_FACTORY_HPP__

/***************************************************************************/

#include "boost\noncopyable.hpp"

/***************************************************************************/

namespace VlogDM
{
	struct Dimension;
	struct Range;
	struct Expression;
	struct ExpressionRange;
	struct Location;
}

/***************************************************************************/

namespace VlogDM {
namespace Writable{

/***************************************************************************/

struct ItemsFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual ~ItemsFactory() {}

	virtual std::unique_ptr< Dimension > newPackedDimension( 
			Location const& _location
		,	std::unique_ptr< Range > _range
	) const = 0;
	
	virtual std::unique_ptr< Range > newExpressionRange( 
			Location const& _location
		,	std::unique_ptr< Expression > _lhs
		,	std::unique_ptr< Expression > _rhs
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_ITEMS_FACTORY_HPP__
