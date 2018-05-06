#ifndef __EC_SYNTAX_ERROR_HPP__
#define __EC_SYNTAX_ERROR_HPP__

/***************************************************************************/

#include "entry_controller\api\errors\ec_isyntax_error.hpp"
#include "entry_controller\sources\errors\ec_base_import_error.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

class SyntaxError
	:	public BaseImportError< ISyntaxError >
{

/***************************************************************************/

	typedef
		BaseImportError< ISyntaxError >
		BaseClass;

	using BaseClass::BaseImportError;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_SYNTAX_ERROR_HPP__
