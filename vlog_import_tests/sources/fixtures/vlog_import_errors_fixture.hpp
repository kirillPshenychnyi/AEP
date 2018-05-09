#ifndef __VLOG_IMPORT_ERRORS_FIXTURE_HPP__
#define __VLOG_IMPORT_ERRORS_FIXTURE_HPP__

/***************************************************************************/

#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

/***************************************************************************/

namespace EntryController 
{

/***************************************************************************/

	namespace Errors 
	{ 
		struct IImportErrorsSet;
	}

/***************************************************************************/

}

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

class ImportErrorsFixture
	:	public BaseFixture
{

/***************************************************************************/
	
	struct ErrorsHelper
	{
		explicit ErrorsHelper(
			EntryController::Errors::IImportErrorsSet const & _importErrors 
		);

		ErrorsHelper & syntaxError( int _line );

		ErrorsHelper & undeclaredId( int _line, std::string const & _id );

		EntryController::Errors::IImportErrorsSet const & m_importErrors;

		int m_currentErrorIdx;
	};

/***************************************************************************/

public:

/***************************************************************************/

	ErrorsHelper & expectErrors( int _errors );

/***************************************************************************/

	std::unique_ptr< ErrorsHelper > m_helper;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_IMPORT_ERRORS_FIXTURE_HPP__
