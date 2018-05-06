#ifndef __EC_BASE_IMPORT_ERROR_HPP__
#define __EC_BASE_IMPORT_ERROR_HPP__

/***************************************************************************/

#include "entry_controller\api\errors\ec_import_error_visitor.hpp"
#include "entry_controller\api\errors\ec_import_error_cast.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

template < typename _TBase >
class BaseImportError
	:	public _TBase
{

/***************************************************************************/

public:

/***************************************************************************/

	BaseImportError( 
			std::string const& _fileName
		,	int _beginLine
		,	int _beginColumn
	)
		:	m_fileName( _fileName )
		,	m_beginLineNumber( _beginLine )
		,	m_beginColumnNumber( _beginColumn )
	{
	}

/***************************************************************************/

public:

/***************************************************************************/

	std::string const & getFileName() const final
	{
		return m_fileName;
	}

	int getBeginLineNumber() const final
	{
		return m_beginLineNumber;
	}

	int getBeginColumnNumber() const final
	{
		return m_beginColumnNumber;
	}

	void accept( ImportErrorVisitor & _errorVisitor ) const final
	{
		_errorVisitor.visit( *this );
	}

	std::size_t hash() const override
	{
		std::size_t seed = 0;

		boost::hash_combine( seed, m_beginLineNumber );
		boost::hash_combine( seed, m_beginColumnNumber );

		return seed;
	}

	bool isEqualTo( ImportError const & _error ) const override
	{
		ImportErrorCast< _TBase > caster;

		auto castResult = caster.cast( _error );

		return
			castResult
		&&	m_beginColumnNumber == _error.getBeginColumnNumber()
		&&	m_beginLineNumber == _error.getBeginLineNumber()
		&&	m_fileName == _error.getFileName();
	}

/***************************************************************************/

private:

/***************************************************************************/

	std::string const m_fileName;

	const int m_beginLineNumber;

	const int m_beginColumnNumber;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_BASE_IMPORT_EXCEPTION_HPP__
