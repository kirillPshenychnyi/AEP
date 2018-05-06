#ifndef __EC_IBASE_IMPORT_ERROR_HPP__
#define __EC_IBASE_IMPORT_ERROR_HPP__

/***************************************************************************/

#include "entry_controller\api\errors\ec_import_error_visitor.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

struct ImportError
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual std::string const & getFileName() const = 0;

	virtual int getBeginLineNumber() const = 0;

	virtual int getBeginColumnNumber() const = 0;

	virtual void accept( ImportErrorVisitor & _errorVisitor ) const = 0;

	virtual std::size_t hash() const = 0;

	virtual bool isEqualTo( ImportError const & _error ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_IBASE_IMPORT_ERROR_HPP__
