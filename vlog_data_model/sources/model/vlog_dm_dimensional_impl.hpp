#ifndef __VLOG_DM_DIMENSIONAL_IMPL_HPP__
#define __VLOG_DM_DIMENSIONAL_IMPL_HPP__

/***************************************************************************/

#include <boost\scoped_ptr.hpp>

#include "vlog_data_model\api\vlog_dm_dimension.hpp"

#include "common_tools\utils\convertors.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

template< typename _BaseClass > 
class DimensionalImpl
	:	public _BaseClass
{

/***************************************************************************/

	boost::optional< Dimension const & > getDimension() const final;

/***************************************************************************/

protected:

/***************************************************************************/

	void setDimension( std::unique_ptr< Dimension > _dimension );

/***************************************************************************/

private:

/***************************************************************************/
	
	boost::scoped_ptr< Dimension > m_dimension;

/***************************************************************************/

};

/***************************************************************************/

template< typename _BaseClass >
inline
boost::optional< Dimension const& >
DimensionalImpl< _BaseClass >::getDimension() const
{
	return 
		Tools::Convertors::convertPointerToOptional( m_dimension.get() );
}

/***************************************************************************/

template< typename _BaseClass >
inline 
void 
DimensionalImpl< _BaseClass >::setDimension( std::unique_ptr<Dimension> _dimension )
{
	m_dimension.reset( _dimension.release() );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DIMENSIONAL_IMPL_HPP__
