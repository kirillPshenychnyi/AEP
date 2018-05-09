#include "stdafx.h"

#include "entry_controller\sources\errors\ec_errors_factory.hpp"

#include "entry_controller\sources\errors\ec_undeclared_identifier_error.hpp"
#include "entry_controller\sources\errors\ec_syntax_error.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

std::unique_ptr< IUndeclaredIdentifierError >
ErrorsFactory::newUndeclaredIdentifierError( antlr4::ParserRuleContext & _ctx )
{
	antlr4::Token const & token = *_ctx.getStart();
	 
	return 
		std::make_unique< UndeclaredIdentifierError > (
					_ctx.children.front()->getText()
				,	token.getInputStream()->getSourceName()
				,	token.getLine()
				,	token.getCharPositionInLine() 
		);
}

/***************************************************************************/

std::unique_ptr< ISyntaxError >
ErrorsFactory::newSyntaxError( antlr4::Token const & _token )
{
	return 
		std::make_unique< SyntaxError >(
				_token.getInputStream()->getSourceName()
			,	_token.getLine()
			,	_token.getCharPositionInLine() 
		);
}

/***************************************************************************/

}
}