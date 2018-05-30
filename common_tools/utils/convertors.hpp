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

template< class _EnumType >
typename _EnumType::Kind
toEnumFromString( const char * const _value )
{
	for( 
		int i = static_cast< int >( typename _EnumType::Kind::First );
		i <= static_cast< int >( typename _EnumType::Kind::Last ); 
		++i 
	)
	{
		typename _EnumType::Kind toCompare 
			= static_cast< typename _EnumType::Kind >( i );

		if( !strcmp( _value, _EnumType::toString( toCompare ) ) )
			return toCompare;
	}

	return typename _EnumType::Kind::First;
}

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__CONVERTORS_HPP__
