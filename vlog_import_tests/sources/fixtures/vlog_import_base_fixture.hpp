#ifndef __VLOG_IMPORT_BASE_FIXTURE_HPP__
#define __VLOG_IMPORT_BASE_FIXTURE_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "vlog_import_tests\catch.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

class BaseFixture
	:	public boost::noncopyable
{

/***************************************************************************/

public:

/***************************************************************************/

	void runImport( std::string const & _code );

	template< typename _TSource, typename _TTarget, template < typename > class _TVisitor >
	_TTarget const & checkCast( _TSource const& _source );

/***************************************************************************/

};

/***************************************************************************/

template< typename _TSource, typename _TTarget, template < typename > class _TVisitor >
inline 
_TTarget const & 
BaseFixture::checkCast( _TSource const & _source )
{
	_TVisitor< _TTarget > caster;

	auto castRes = caster.cast( _source );

	REQUIRE( castRes.is_initialized() );

	return *castRes;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_IMPORT_BASE_FIXTURE_HPP__
