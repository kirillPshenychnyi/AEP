#ifndef __EC_IERRORS_SET_HPP
#define __EC_IERRORS_SET_HPP

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

struct ImportError;

/***************************************************************************/

struct IImportErrorsSet
	:	public boost::noncopyable
{

/***************************************************************************/

	typedef
		std::unique_ptr< ImportError >
		ErrorPtr;

	typedef
		std::function< void ( ImportError const& ) >
		ErrorCallback;

/***************************************************************************/

	virtual ~IImportErrorsSet() = default;

	virtual void addError( ErrorPtr _error ) = 0;

	virtual void forEachError( ErrorCallback _callback ) const = 0;

	virtual bool hasErrors() const = 0;

	virtual int getErrorsCount() const = 0;

	virtual ImportError const & getError ( int _idx ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/
 
#endif // !__EC_IERRORS_SET_HPP
