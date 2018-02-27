#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_items_factory_impl.hpp"

#include "vlog_data_model\api\vlog_dm_expression.hpp"

#include "vlog_data_model\sources\model\vlog_dm_base_identifier_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_dimension_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_part_select_range_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_expression_range_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_multidimensional_range_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_continuous_assignment_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_sequential_process_impl.hpp"

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
ItemsFactoryImpl::newUnackedDimension( Location const& _location, RangePtr _range ) const
{
	return newDimension< UnpackedDimensionImpl >( _location, std::move( _range ) );
}

/***************************************************************************/

template< typename _Dimension >
DimensionPtr
ItemsFactoryImpl::newDimension( Location const& _location, RangePtr _range ) const
{
	return std::make_unique< _Dimension >( _location, std::move( _range ) );
}

/***************************************************************************/

RangePtr
ItemsFactoryImpl::newPartSelectRange( 
		Location const & _location
	,	ExpressionPtr _leftBound
	,	ExpressionPtr _rightBound 
) const
{
	return 
		std::make_unique< PartSelectRangeImpl >( 
				_location
			,	std::move( _leftBound )
			,	std::move( _rightBound ) 
		);
}

/***************************************************************************/

RangePtr 
ItemsFactoryImpl::newExpressionRange( ExpressionPtr _expression ) const
{
	return std::make_unique< ExpressionRangeImpl >( std::move( _expression ) );
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

BaseIdentifierPtr 
ItemsFactoryImpl::newIdentifier(
		Location const& _location
	,	Declared const & _declared
	,	RangePtr _range
	) const
{
	if( _range )
		return std::make_unique< BaseIdentifierImpl< true > >( 
						_location
					,	_declared 
					,	std::move( _range )
				);

	return std::make_unique< BaseIdentifierImpl< false > >( _location, _declared );
}

/***************************************************************************/

ContinuousAssignmentPtr
ItemsFactoryImpl::newContinuousAssignment(
		Location const& _location
	,	std::unique_ptr< BinaryOperator > _assignment
	) const
{
	return 
		std::make_unique< ContinuousAssignmentImpl >( 
				_location
			,	std::move( _assignment ) 
		);
}

/***************************************************************************/

SequentialProcessPtr 
ItemsFactoryImpl::newSequentialProcess( 
		Location const & _location
	,	StatementPtr _statement 
) const
{
	return 
		std::make_unique< SequentialProcessImpl >( 
				_location
			,	std::move( _statement ) 
		);
}

/***************************************************************************/

}