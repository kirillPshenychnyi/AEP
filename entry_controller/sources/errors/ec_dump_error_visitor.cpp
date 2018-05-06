#include "stdafx.h"

#include "entry_controller\sources\errors\ec_dump_error_visitor.hpp"
#include "entry_controller\sources\errors\ec_error_messages.hpp"
#include "entry_controller\api\errors\ec_iundeclared_identifier_error.hpp"
#include "entry_controller\api\errors\ec_isyntax_error.hpp"

#include "common_tools\utils\string_utils.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

DumpErrorVisitor::DumpErrorVisitor( std::ostream & _ostream )
	:	m_targetStream( _ostream )
{
}

/***************************************************************************/

void 
DumpErrorVisitor::visit( IUndeclaredIdentifierError const & _undeclaredId )
{
	m_targetStream 
		<<	Tools::fillTemplate( 
					Messages::UndeclaredIdErrorMessage
				,	_undeclaredId.getIdentifier()
				,	_undeclaredId.getFileName()
				,	_undeclaredId.getBeginLineNumber()
				,	_undeclaredId.getBeginColumnNumber()
			)
		<< std::endl;
}

/***************************************************************************/

void 
DumpErrorVisitor::visit( ISyntaxError const & _syntaxError )
{
	m_targetStream 
		<<	Tools::fillTemplate( 
					Messages::SyntaxtErrorMessage
				,	_syntaxError.getFileName()
				,	_syntaxError.getBeginLineNumber()
				,	_syntaxError.getBeginColumnNumber()
			)
		<< std::endl;
}

/***************************************************************************/

}
}