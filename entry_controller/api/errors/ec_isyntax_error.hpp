#ifndef __EC_ISYNTAX_ERROR_HPP__
#define __EC_ISYNTAX_ERROR_HPP__

/***************************************************************************/

#include "entry_controller\api\errors\ec_ibase_import_error.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

struct ISyntaxError
	:	public ImportError
{
};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_ISYNTAX_ERROR_HPP__
