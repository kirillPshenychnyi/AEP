#ifndef __VLOG_IMPORT_BASE_FIXTURE_HPP__
#define __VLOG_IMPORT_BASE_FIXTURE_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "vlog_import_tests\catch.hpp"
#include "hypodermic\Hypodermic.h"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

struct ContainerBootstrapper
{

/***************************************************************************/

	ContainerBootstrapper();

/***************************************************************************/

	std::shared_ptr< Hypodermic::Container > m_container;

/***************************************************************************/

};

/***************************************************************************/

class BaseFixture
	:	public boost::noncopyable
{

/***************************************************************************/

public:

/***************************************************************************/

	void runImport( std::string const & _code );

	template< typename _TSource, typename _TTarget, template < typename > class _TVisitor >
	static _TTarget const & checkCast( _TSource const& _source );

/***************************************************************************/

protected:

/***************************************************************************/

	static ContainerBootstrapper m_bootstrapper;

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
