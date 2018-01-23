#ifndef __TOOLS_COLLECTION_UTILS
#define __TOOLS_COLLECTION_UTILS
 
/***************************************************************************/

#include <boost\functional\hash\hash.hpp>

/***************************************************************************/

namespace Tools {
namespace Collections {

/***************************************************************************/

template< typename _Value >
struct NamedHasher
{

/***************************************************************************/

	std::size_t operator()( _Value const & _value ) const
	{	
		return operator()( _value->getName() );
	}

	std::size_t operator()( std::string const & _name ) const
	{
		return boost::hash_value( _name );
	}

/***************************************************************************/

};

/***************************************************************************/

template< typename _Value >
struct NamedComparator
{
	bool operator()( _Value const & _lhs, _Value const & _rhs ) const
	{
		return operator()( _lhs->getName(), _rhs );
	}

	bool operator()( _Value const & _lhs, std::string const & _rhs ) const
	{
		return operator()( _rhs, _lhs );
	}

	bool operator()( std::string const & _lhs, _Value const & _rhs ) const
	{
		return _lhs == _rhs->getName();
	}
};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__TOOLS_COLLECTION_UTILS
