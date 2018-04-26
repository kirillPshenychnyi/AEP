#ifndef __STRING_UTILS_HPP__
#define __STRING_UTILS_HPP__

/***************************************************************************/

#include <boost\format.hpp>

/***************************************************************************/

namespace Tools {

/***************************************************************************/

template< typename ... _Args >
inline
std::string 
fillTemplate( std::string const & _template, _Args ..._args )
{
	return format( boost::format( _template ), _args... );
}

/***************************************************************************/

std::string 
inline
format( boost::format & _pattern )
{
	return _pattern.str();
}

/***************************************************************************/

template< typename _T, typename ... Args >
inline
std::string 
format( boost::format & _pattern, _T _arg, Args ... _args)
{
	_pattern % _arg;
	return format( _pattern, _args... );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__STRING_UTILS_HPP__
