#include "stdafx.h"

#include "aep_model\model\contexts\aep_model_assertion_context_set_impl.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

void
AssertionContextSetImpl::addContext( AssertionContextPtr _context )
{
	m_contexts.insert( std::move( _context ) );
}

/***************************************************************************/

bool 
AssertionContextSetImpl::hasAssertionContext( std::string const & _dutName ) const
{
	return
			m_contexts.find( _dutName, ContextHasher(), ContextComparator() ) 
		!=	m_contexts.end();
}

/***************************************************************************/

void 
AssertionContextSetImpl::forEachAssertionContext( 
	AssertionContextCallback _callBack 
) const
{
	for( auto const & context : m_contexts )
		_callBack( *context );
}

/***************************************************************************/

void 
AssertionContextSetImpl::forEachConstAssertionContext( 
	ConstAssertionContextCallback _callBack 
) const
{
	for( auto & context : m_contexts )
		_callBack( *context );
}

/***************************************************************************/

/***************************************************************************/

int 
AssertionContextSetImpl::getContextsCount() const
{
	return m_contexts.size();
}

/***************************************************************************/

boost::optional< AssertionContext & >
AssertionContextSetImpl::takeContext( std::string const & _dutName )
{
	auto it = m_contexts.find( _dutName, ContextHasher(), ContextComparator() );

	return 
		it != m_contexts.end()
		?	**it
		:	boost::optional< AssertionContext & >();
}

/***************************************************************************/

boost::optional< AssertionContext const & > 
AssertionContextSetImpl::getContext( std::string const & _dutName ) const
{
	auto it = m_contexts.find( _dutName, ContextHasher(), ContextComparator() );

	return 
		it != m_contexts.end()
		?	**it
		:	boost::optional< AssertionContext const & >();
}

/***************************************************************************/

void 
AssertionContextSetImpl::clear()
{
	m_contexts.clear();
}

/***************************************************************************/

}