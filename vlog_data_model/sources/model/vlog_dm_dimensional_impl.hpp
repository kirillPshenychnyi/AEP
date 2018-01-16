#ifndef __VLOG_DM_DIMENSIONAL_IMPL__
#define __VLOG_DM_DIMENSIONAL_IMPL__

/***************************************************************************/

#include "boost\scoped_ptr.hpp"

#include "sources\model\vlog_dm_declared_impl.hpp"

#include "vlog_data_model\api\vlog_dm_dimension.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

template < typename _BaseClass > 
class DimensionalImpl
	:	public DeclaredImpl< _BaseClass >
{

/***************************************************************************/

	typedef
		DeclaredImpl< _BaseClass >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	virtual ~DimensionalImpl() {}

	DimensionalImpl( 
			Declaration const & _declaration
		,	std::string const & _name
		,	Location const & _location
		,	std::unique_ptr< Dimension > _dimension 
	);

	boost::optional< Dimension const & > getDimension() const override;

/***************************************************************************/

private:

/***************************************************************************/
	
	boost::scoped_ptr< Dimension > m_dimension;

/***************************************************************************/

};

/***************************************************************************/

template< typename _BaseClass >
inline
DimensionalImpl< _BaseClass >::DimensionalImpl( 
		Declaration const & _declaration
	,	std::string const & _name
	,	Location const & _location
	,	std::unique_ptr< Dimension > _dimension 
	)
	:	BaseClass( _declaration, _name, _location )
	,	m_dimension( _dimension.release() )
{

}

/***************************************************************************/

template< typename _BaseClass >
inline
boost::optional< Dimension const & > 
DimensionalImpl< _BaseClass >::getDimension() const
{
	return boost::none;
}

/***************************************************************************/

}

#endif // !__VLOG_DM_DIMENSIONAL_IMPL__
