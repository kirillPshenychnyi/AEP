#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_items_factory_impl.hpp"

#include "vlog_data_model\api\vlog_dm_expression.hpp"

#include "vlog_data_model\sources\model\vlog_dm_dimension_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_part_select_range_impl.hpp"

/***************************************************************************/

namespace VlogDM { 

/***************************************************************************/

std::unique_ptr<Dimension> 
ItemsFactoryImpl::newPackedDimension( 
		Location const & _location
	,	std::unique_ptr<Range> _range 
	) const
{
	return std::make_unique< PackedDimensionImpl >( _location, std::move( _range ) );
}

/***************************************************************************/

std::unique_ptr< Range >
ItemsFactoryImpl::newPartSelectRange( 
		Location const & _location
	,	std::unique_ptr< Expression > _lhs
	,	std::unique_ptr< Expression > _rhs 
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

}