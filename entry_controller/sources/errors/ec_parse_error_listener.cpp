#include "stdafx.h"

#include "entry_controller\sources\errors\ec_parse_error_listener.hpp"
#include "entry_controller\sources\errors\ec_errors_factory.hpp"

#include "entry_controller\api\errors\ec_iimport_errors_set.hpp"
#include "entry_controller\api\errors\ec_isyntax_error.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

ParseErrorListener::ParseErrorListener( IImportErrorsSet & _errorsSet )
	:	m_errorsSet( _errorsSet )
{
}

/***************************************************************************/

void
ParseErrorListener::syntaxError(
		antlr4::Recognizer *recognizer
	,	antlr4::Token *offendingSymbol
	,	size_t line
	,	size_t charPositionInLine
	,	const std::string &msg
	,	std::exception_ptr e
)
{
	m_errorsSet.addError( ErrorsFactory::newSyntaxError( *offendingSymbol ) );
}

/***************************************************************************/

}
}