#ifndef __EC_PARSE_ERROR_LISTENER_HPP__
#define __EC_PARSE_ERROR_LISTENER_HPP__

/***************************************************************************/

#include "ANTLRGenerated\Verilog2001Parser.h"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

struct IImportErrorsSet;

/***************************************************************************/

class ParseErrorListener
	:	public antlr4::BaseErrorListener
{

/***************************************************************************/

public:

/***************************************************************************/

	ParseErrorListener( IImportErrorsSet & _errorsSet );

/***************************************************************************/

	void syntaxError(
			antlr4::Recognizer *recognizer
		,	antlr4::Token *offendingSymbol
		,	size_t line
		,	size_t charPositionInLine
		,	const std::string &msg
		,	std::exception_ptr e
	) final;

/***************************************************************************/

private:

/***************************************************************************/

	IImportErrorsSet & m_errorsSet;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_PARSE_ERROR_LISTENER_HPP__
