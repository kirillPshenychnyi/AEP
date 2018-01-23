#include "stdafx.h"

#include "vlog_data_model\sources\model\vlog_dm_part_select_range_impl.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_range_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

PartSelectRangeImpl::PartSelectRangeImpl(
		Location const& _location
	,	std::unique_ptr< Expression > _leftBound
	,	std::unique_ptr< Expression > _rightBound
)	:	BaseClass( _location )
	,	m_leftBound( std::move( _leftBound ) )
	,	m_rightBound( std::move( _rightBound ) )
{
}

/***************************************************************************/

void 
PartSelectRangeImpl::accept( RangeVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}