#ifndef __VLOG_DM_ITEMS_FACTORY_IMPL_HPP__
#define __VLOG_DM_ITEMS_FACTORY_IMPL_HPP__
 
/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ItemsFactoryImpl
	:	public Writable::ItemsFactory
{

/***************************************************************************/

public:

/***************************************************************************/

	DimensionPtr newPackedDimension( 
			Location const& _location
		,	RangePtr _range
	) const override;

	DimensionPtr newUnackedDimension( 
			Location const& _location
		,	RangePtr _range
	) const override;

	RangePtr newPartSelectRange( 
			Location const& _location
		,	ExpressionPtr _lhs
		,	ExpressionPtr _rhs
	) const override;

	Writable::MultidimensionalRangePtr newMultidimensionalRange(
		Location const& _location
	) const override;

/***************************************************************************/

private:

/***************************************************************************/

	template< typename _Dimension >
	DimensionPtr newDimension(
			Location const& _location
		,	RangePtr _range
	) const;

/***************************************************************************/

};
	
/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_ITEMS_FACTORY_IMPL_HPP__
