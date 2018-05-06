#ifndef __VLOG_IMPORT_BASE_FIXTURE_HPP__
#define __VLOG_IMPORT_BASE_FIXTURE_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_import_tests\catch.hpp"
#include "hypodermic\Hypodermic.h"

/***************************************************************************/

namespace EntryController 
{
	struct IAccessor;
}

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

	virtual void runImport( std::string const & _code );

	template< typename _TSource, typename _TTarget, template < typename > class _TVisitor >
	static _TTarget const & checkCast( _TSource const& _source );

	VlogDM::IAccessor const & getVlogDm() const;

	EntryController::IAccessor const & getEntryController() const;

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
