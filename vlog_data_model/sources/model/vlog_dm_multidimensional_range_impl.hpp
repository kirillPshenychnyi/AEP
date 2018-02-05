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

	int getRangesCount() const override;

	Range const& getRange( int _idx ) const override;

	void accept( RangeVisitor & _visitor ) const override;

	void addRange( RangePtr _range ) override;

/***************************************************************************/

private:

/***************************************************************************/

	Ranges m_ranges;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_MULTIDIMENSIONAL_RANGE_IMPL_HPP__
