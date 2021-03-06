#ifndef __LOCATED_IMPL_HPP__
#define __LOCATED_IMPL_HPP__

/***************************************************************************/

#include "api\vlog_dm_location.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

template< typename _BaseClass >
class LocatedImpl
	:	public	_BaseClass
{

/***************************************************************************/
		
public:
		
/***************************************************************************/
			
	LocatedImpl( Location const & _location );

/***************************************************************************/

	Location const & getLocation () const final;

/***************************************************************************/

private:

/***************************************************************************/

	Location m_location;

/***************************************************************************/

};

/***************************************************************************/

template< typename _BaseClass >
inline
LocatedImpl< _BaseClass >::LocatedImpl( Location const & _location )
	:	m_location( _location )
{
}

/***************************************************************************/

template< typename _BaseClass >
inline
Location const & 
LocatedImpl< _BaseClass >::getLocation() const
{
	return m_location; 
}

/***************************************************************************/

}

/***************************************************************************/

#endif // ! __LOCATED_IMPL_HPP__
