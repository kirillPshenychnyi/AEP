#ifndef __AEP_TEST_GENERIC_OBJECT_HELPER_HPP__
#define __AEP_TEST_GENERIC_OBJECT_HELPER_HPP__

/***************************************************************************/

#include "common_tools\catch.hpp"

/***************************************************************************/

namespace AepTest {

/***************************************************************************/

template< 
		typename _TParent
	,	typename _TObject
	,	typename _THasher = std::hash< _TObject > 
>
class GenericObjectHelper
{

/***************************************************************************/

public:

/***************************************************************************/

	using IteratorCallback = std::function< void( _TObject const & ) >;
	using Iterator = std::function< void( IteratorCallback ) >;

	GenericObjectHelper( _TParent & _parent, Iterator _iterator )
		:	m_parent( _parent )
	{
		_iterator.operator()( 
			[ & ]( _TObject const & _item )
			{
				m_actual.insert( _item );
			}
		);
	}

	virtual ~GenericObjectHelper() = default;

	template< typename ... _TArgs >
	GenericObjectHelper operator() ( _TArgs ... _args )
	{
		m_expected.emplace_back( _args... );

		return *this;
	}

/***************************************************************************/

	_TParent & end()
	{
		REQUIRE( m_actual.size() == m_expected.size() );

		for( _TObject const & expected : m_expected )
			REQUIRE( m_actual.find( expected ) != m_actual.end() );

		return m_parent;
	}

/***************************************************************************/

private:

/***************************************************************************/

	std::unordered_set < _TObject, _THasher > m_actual;

	std::vector< _TObject > m_expected;

	_TParent & m_parent;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_TEST_GENERIC_OBJECT_HELPER_HPP__
