#ifndef __EC_ERROR_VISITOR_HPP__
#define __EC_ERROR_VISITOR_HPP__

/***************************************************************************/

#include "common_tools\utils\default_visitor.hpp"
#include "common_tools\utils\base_visitor.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

struct IUndeclaredIdentifierError;
struct ISyntaxError;

/***************************************************************************/

DECLARE_VISITOR( ImportError, IUndeclaredIdentifierError, ISyntaxError )

DECLARE_DEFAULT_VISITOR( ImportError, IUndeclaredIdentifierError, ISyntaxError )

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_ERROR_VISITOR_HPP__
