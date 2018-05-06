#ifndef __EC_UNDECLARED_IDENTIFIER_ERROR_HPP__
#define __EC_UNDECLARED_IDENTIFIER_ERROR_HPP__

/***************************************************************************/

#include "entry_controller\sources\errors\ec_base_import_error.hpp"
#include "entry_controller\api\errors\ec_iundeclared_identifier_error.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

class UndeclaredIdentifierError
	:	public BaseImportError< IUndeclaredIdentifierError >
{

/***************************************************************************/

	typedef
		BaseImportError< IUndeclaredIdentifierError >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	UndeclaredIdentifierError(
			std::string const& _identifier
		,	std::string const& _fileName
		,	int _beginLine
		,	int _beginColumn
	)
		:	BaseClass( _fileName, _beginLine, _beginColumn )
		,	m_identifier( _identifier )
	{
	}

/***************************************************************************/

	std::string const& getIdentifier() const final;

	std::size_t hash() const final;

	bool isEqualTo( ImportError const & _error ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	std::string m_identifier;

/***************************************************************************/

};

/***************************************************************************/

inline
std::string const & 
UndeclaredIdentifierError::getIdentifier() const
{
	return m_identifier;
}

/***************************************************************************/

inline 
std::size_t 
UndeclaredIdentifierError::hash() const
{
	std::size_t baseSeed = BaseClass::hash();
	boost::hash_combine( baseSeed, m_identifier.c_str() );

	return baseSeed;
}

/***************************************************************************/

inline 
bool 
UndeclaredIdentifierError::isEqualTo( ImportError const & _error ) const
{
	bool baseCheck = BaseClass::isEqualTo( _error );

	if( !baseCheck )
		return false;

	IUndeclaredIdentifierError const & other 
			= static_cast< IUndeclaredIdentifierError const & >( _error );

	return m_identifier == other.getIdentifier();
}

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_UNDECLARED_IDENTIFIER_ERROR_HPP__
