#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_items_factory_impl.hpp"

#include "vlog_data_model\api\vlog_dm_expression.hpp"

#include "vlog_data_model\sources\model\vlog_dm_dimension_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_part_select_range_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_multidimensional_range_impl.hpp"

/***************************************************************************/

namespace VlogDM { 

/***************************************************************************/

DimensionPtr
ItemsFactoryImpl::newPackedDimension( 
		Location const & _location
	,	RangePtr _range 
	) const
{
	return newDimension< PackedDimensionImpl >( _location, std::move( _range ) );
}

/***************************************************************************/

DimensionPtr
ItemsFactoryImpl::newUnackedDimension( 
		Location const& _location
	,	RangePtr _range
	) const
{
	return newDimension< UnpackedDimensionImpl >( _location, std::move( _range ) );
}

/***************************************************************************/

template< typename _Dimension >
DimensionPtr
ItemsFactoryImpl::newDimension(
		Location const& _location
	,	RangePtr _range
	) const
{
	return std::make_unique< _Dimension >( _location, std::move( _range ) );
}

/***************************************************************************/

RangePtr
ItemsFactoryImpl::newPartSelectRange( 
		Location const & _location
	,	ExpressionPtr _lhs
	,	ExpressionPtr _rhs 
	) const
{
	return 
		std::make_unique< PartSelectRangeImpl >( 
				_location
			,	std::move( _lhs )
			,	std::move( _rhs ) 
		);
}

/***************************************************************************/

Writable::MultidimensionalRangePtr 
ItemsFactoryImpl::newMultidimensionalRange(
		Location const& _location
	) const
{
	return std::make_unique< MultidimensionalRangeImpl >( _location );
}

/***************************************************************************/

}