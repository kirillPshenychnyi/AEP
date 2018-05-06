#ifndef __EC_ERROR_CAST_HPP__
#define __EC_ERROR_CAST_HPP__

/***************************************************************************/

#include "entry_controller\api\errors\ec_ibase_import_error.hpp"
#include "entry_controller\api\errors\ec_import_error_visitor.hpp"
#include "common_tools\utils\visitor_cast.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

DEFINE_CAST( ImportError )

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_ERROR_CAST_HPP__
