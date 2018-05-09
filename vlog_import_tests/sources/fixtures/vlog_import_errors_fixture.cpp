#include "stdafx.h"

#include "vlog_import_tests\sources\fixtures\vlog_import_errors_fixture.hpp"
#include "entry_controller\api\errors\ec_iimport_errors_set.hpp"
#include "entry_controller\api\errors\ec_isyntax_error.hpp"
#include "entry_controller\api\errors\ec_iundeclared_identifier_error.hpp"
#include "entry_controller\api\errors\ec_import_error_cast.hpp"

#include "entry_controller\api\ec_iaccessor.hpp"

#include "common_tools\utils\string_utils.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

ImportErrorsFixture::ErrorsHelper::ErrorsHelper( 
	EntryController::Errors::IImportErrorsSet const & _importErrors
)
	:	m_importErrors( _importErrors )
	,	m_currentErrorIdx( 0 )
{
}

/***************************************************************************/

ImportErrorsFixture::ErrorsHelper & 
ImportErrorsFixture::ErrorsHelper::syntaxError( int _line )
{
	using namespace EntryController::Errors;

	ImportError const & error = m_importErrors.getError( m_currentErrorIdx );

	ISyntaxError const & castRes 
		= checkCast< ImportError, ISyntaxError, ImportErrorCast >( error );

	REQUIRE( castRes.getBeginLineNumber() == _line );

	m_currentErrorIdx++;
	return *this;
}

/***************************************************************************/

ImportErrorsFixture::ErrorsHelper & 
ImportErrorsFixture::ErrorsHelper::undeclaredId( int _line, std::string const & _id )
{
	using namespace EntryController::Errors;

	ImportError const & error = m_importErrors.getError( m_currentErrorIdx );

	IUndeclaredIdentifierError const & castRes 
		= checkCast< ImportError, IUndeclaredIdentifierError, ImportErrorCast >( error );

	REQUIRE( castRes.getBeginLineNumber() == _line );
	REQUIRE( castRes.getIdentifier() == _id );

	m_currentErrorIdx++;

	return *this;
}

/***************************************************************************/

ImportErrorsFixture::ErrorsHelper &
ImportErrorsFixture::expectErrors( int _errors )
{
	static std::string errorsCountMistmatch( 
		"Errors count mistmatch\n expected:\t %1%\n actual:\t %2%"
	);

	auto const & errorsSet = getEntryController().getImportErrors();

	if( errorsSet.getErrorsCount() != _errors )
		FAIL( 
			Tools::fillTemplate( 
					errorsCountMistmatch
				,	_errors
				,	errorsSet.getErrorsCount() 
			) 
		);

	if( !m_helper )
		m_helper.reset( new ErrorsHelper( errorsSet ) );

	return *m_helper;
}

/***************************************************************************/

}