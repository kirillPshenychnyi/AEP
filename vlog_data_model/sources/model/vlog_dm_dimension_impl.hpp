#ifndef __VLOG_DM_DIMENSION_IMPL_HPP__
#define __VLOG_DM_DIMENSION_IMPL_HPP__

/***************************************************************************/

#include "common_tools\utils\convertors.hpp"

#include "vlog_data_model\api\vlog_dm_range.hpp"

#include "vlog_data_model\api\vlog_dm_packed_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_unpacked_dimension.hpp"

#include "vlog_data_model\api\vlog_dm_dimension_visitor.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

template< typename _BaseClass >
class DimensionBaseImpl
	:	public LocatedImpl< _BaseClass >
{

/***************************************************************************/

	typedef
		LocatedImpl< _BaseClass >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	DimensionBaseImpl( 
			Location const & _location
		,	std::unique_ptr<Range> _range 
		)
		:	BaseClass( _location )
		,	m_range( _range.release() )
	{}

	boost::optional< Range const & > getRange() const override
	{
		return Tools::Convertors::convertPointerToOptional( m_range.get() );
	}

/***************************************************************************/

private:

/***************************************************************************/

	std::unique_ptr< Range > m_range;

/***************************************************************************/

};

/***************************************************************************/

class PackedDimensionImpl
	:	public DimensionBaseImpl< PackedDimension >
{

/***************************************************************************/

	typedef
		DimensionBaseImpl< PackedDimension >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	PackedDimensionImpl( 
			Location const & _location
		,	std::unique_ptr< Range > _range 
		)
		:	BaseClass( _location, std::move( _range ) )
	{}

	void accept( DimensionVisitor & _visitor ) const override
	{
		_visitor.visit( *this );
	}

/***************************************************************************/

};

/***************************************************************************/

class UnpackedDimensionImpl
	:	public DimensionBaseImpl< UnpackedDimension >
{

/***************************************************************************/

	typedef
		DimensionBaseImpl< UnpackedDimension >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	UnpackedDimensionImpl( 
			Location const & _location
		,	std::unique_ptr< Range > _range 
		)
		:	BaseClass( _location, std::move( _range ) )
	{}

	void accept( DimensionVisitor & _visitor ) const override
	{
		_visitor.visit( *this );
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DIMENSION_IMPL_HPP__
