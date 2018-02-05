
#include "stdafx.h"

#include "vlog_data_model\sources\model\vlog_dm_multidimensional_range_impl.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_range_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

MultidimensionalRangeImpl::MultidimensionalRangeImpl( const Location & _location )
	:	BaseClass( _location )
{
}

/***************************************************************************/

int MultidimensionalRangeImpl::getRangesCount() const
{
	return m_ranges.size();
}

/***************************************************************************/

Range const & 
MultidimensionalRangeImpl::getRange( int _idx ) const
{
	return *m_ranges[ _idx ];
}

/***************************************************************************/

void 
MultidimensionalRangeImpl::accept( RangeVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

void 
MultidimensionalRangeImpl::addRange( RangePtr _range )
{
	m_ranges.emplace_back( std::move( _range ) );
}

/***************************************************************************/

}