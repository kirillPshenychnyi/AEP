#ifndef __VLOG_DM_TYPE_BASE_IMPL_HPP__
#define __VLOG_DM_TYPE_BASE_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_dimensional_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

template< typename _BaseClass, class _Enum  >
class TypeBaseImpl
	:	public DimensionalImpl< _BaseClass >
{

/***************************************************************************/

public:

/***************************************************************************/

	TypeBaseImpl( 
			std::unique_ptr< Dimension > _dimension
		,	typename _Enum::Kind _kind 
		)
		:	m_kind( _kind )
	{
		setDimension( std::move( _dimension ) );
	}

/***************************************************************************/

	typename _Enum::Kind getKind() const final
	{
		return m_kind;
	}

/***************************************************************************/

private:

/***************************************************************************/

	const typename _Enum::Kind m_kind;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_TYPE_BASE_IMPL_HPP__
