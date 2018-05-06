#ifndef __EC_IUNDECLARED_IDENTIFIER_ERROR_HPP__
#define __EC_IUNDECLARED_IDENTIFIER_ERROR_HPP__

/***************************************************************************/

#include "entry_controller\api\errors\ec_ibase_import_error.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

struct IUndeclaredIdentifierError
	:	public ImportError
{

/***************************************************************************/

	virtual std::string const & getIdentifier() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_IUNDECLARED_IDENTIFIER_ERROR_HPP__
