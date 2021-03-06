#ifndef __EC_DUMP_ERROR_VISITOR_HPP__
#define __EC_DUMP_ERROR_VISITOR_HPP__

/***************************************************************************/

#include "entry_controller\api\errors\ec_import_error_visitor.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

class DumpErrorVisitor
	:	public ImportErrorVisitor
{

/***************************************************************************/

public:

/***************************************************************************/

	DumpErrorVisitor( std::ostream & _ostream );

/***************************************************************************/

	void visit( IUndeclaredIdentifierError const & _undeclaredId ) final;

	void visit( ISyntaxError const & _syntaxError ) final;

/***************************************************************************/

private:

/***************************************************************************/

	std::ostream & m_targetStream;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_DUMP_ERROR_VISITOR_HPP__
