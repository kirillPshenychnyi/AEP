#include "stdafx.h"
#include "entry_controller\sources\errors\ec_errors_set.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

void
ErrorsSet::addError( ErrorPtr _error )
{
	m_errors.add( _error.release() );
}

/***************************************************************************/

void 
ErrorsSet::forEachError( ErrorCallback _callback ) const
{
	for( auto error : m_errors.asVector() )
		_callback( *error );
}

/***************************************************************************/

bool 
ErrorsSet::hasErrors() const
{
	return !m_errors.empty();
}

/***************************************************************************/

}
}