#ifndef __VLOG_IMPORT_BASE_MODULE_ITEMS_FIXTURE_HPP__
#define __VLOG_IMPORT_BASE_MODULE_ITEMS_FIXTURE_HPP__

/***************************************************************************/

#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

#include <vector>

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

#define LINES( _begin, _end )		\
	std::make_pair( _begin, _end )

/***************************************************************************/

class BaseModuleItemsFixture
	:	public BaseFixture
{

/***************************************************************************/

public:

/***************************************************************************/

	typedef
		std::vector< std::string >
		CodeLines;

	typedef
		std::pair< int, int >
		Lines;

/***************************************************************************/

public:

/***************************************************************************/

	void checkCorrectImport( 
			std::string const & _actual
		,	Lines const & _expected 
	);

	void runImport( std::string const & _code ) override;

/***************************************************************************/

private:

/***************************************************************************/

	CodeLines m_lines;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_IMPORT_BASE_ITEMS_FIXTURE_HPP__
