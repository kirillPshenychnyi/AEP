#ifndef __CONVERTORS_HPP__
#define __CONVERTORS_HPP__

/***************************************************************************/

namespace Tools { 
namespace Convertors {

/***************************************************************************/

template< typename _T >
boost::optional< _T const& > 
convertPointerToOptional( const _T * const _value )
{
	return
		_value
	?	*_value
	:	boost::optional< _T const& >();
}

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__CONVERTORS_HPP__
