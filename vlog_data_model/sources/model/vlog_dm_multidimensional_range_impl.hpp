#ifndef __VLOG_DM_MULTIDIMENSIONAL_RANGE_IMPL_HPP__
#define __VLOG_DM_MULTIDIMENSIONAL_RANGE_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_multidimensional_range.hpp"
#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include <vector>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class MultidimensionalRangeImpl
	:	public LocatedImpl< Writable::MultidimensionalRange >
{

/***************************************************************************/

	typedef
		LocatedImpl< Writable::MultidimensionalRange >
		BaseClass;

	typedef
		std::unique_ptr< Range >
		RangePtr;

	typedef
		std::vector< RangePtr >
		Ranges;

/***************************************************************************/

public:

/***************************************************************************/

	MultidimensionalRangeImpl( const Location & _location );

/***************************************************************************/

	int getRangesCount() const final;

	Range const& getRange( int _idx ) const final;

	void accept( RangeVisitor & _visitor ) const final;

	void addRange( RangePtr _range ) final;

/***************************************************************************/

private:

/***************************************************************************/

	Ranges m_ranges;

/***************************************************************************/

};

/***************************************************************************/

inline
MultidimensionalRangeImpl::MultidimensionalRangeImpl( const Location & _location )
	:	BaseClass( _location )
{
}

/***************************************************************************/

inline
int 
MultidimensionalRangeImpl::getRangesCount() const
{
	return m_ranges.size();
}

/***************************************************************************/

inline
Range const & 
MultidimensionalRangeImpl::getRange( int _idx ) const
{
	return *m_ranges[ _idx ];
}

/***************************************************************************/

inline
void 
MultidimensionalRangeImpl::accept( RangeVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

inline
void 
MultidimensionalRangeImpl::addRange( RangePtr _range )
{
	m_ranges.emplace_back( std::move( _range ) );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_MULTIDIMENSIONAL_RANGE_IMPL_HPP__
