#ifndef __VLOG_DM_DIMENSIONAL_OBJECT_IMPL_HPP__
#define __VLOG_DM_DIMENSIONAL_OBJECT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_declared_impl.hpp"

#include "vlog_data_model\sources\model\vlog_dm_dimensional_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

template < typename _BaseClass > 
class DimensionalObjectImpl
	:	public DeclaredImpl< DimensionalImpl< _BaseClass > >
{

/***************************************************************************/

	typedef
		DeclaredImpl< DimensionalImpl< _BaseClass > >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	DimensionalObjectImpl( 
			Declaration const & _declaration
		,	std::string const & _name
		,	Location const & _location
		,	std::unique_ptr< Dimension > _dimension 
	);

/***************************************************************************/

};

/***************************************************************************/

template< typename _BaseClass >
inline
DimensionalObjectImpl< _BaseClass >::DimensionalObjectImpl( 
		Declaration const & _declaration
	,	std::string const & _name
	,	Location const & _location
	,	std::unique_ptr< Dimension > _dimension 
	)
	:	BaseClass( _declaration, _name, _location )
{
	setDimension( std::move( _dimension ) );
}

/***************************************************************************/

}

#endif // !__VLOG_DM_DIMENSIONAL_OBJECT_IMPL_HPP__
