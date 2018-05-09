#ifndef __EC_EXCEPTIONS_FACTORY_HPP__
#define __EC_EXCEPTIONS_FACTORY_HPP__

/***************************************************************************/

#include "entry_controller\ANTLRGenerated\Verilog2001BaseVisitor.h"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

struct IUndeclaredIdentifierError;
struct ISyntaxError;

/***************************************************************************/

struct ErrorsFactory { 

/***************************************************************************/

	static std::unique_ptr< IUndeclaredIdentifierError >
	newUndeclaredIdentifierError( antlr4::ParserRuleContext & _ctx );

	static std::unique_ptr< ISyntaxError >
	newSyntaxError( antlr4::Token const & _token );

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_EXCEPTIONS_FACTORY_HPP__
