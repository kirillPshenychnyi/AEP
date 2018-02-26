#include "stdafx.h"

#include "vlog_import_tests\sources\fixtures\vlog_import_base_module_items_fixture.hpp"

#include <boost\algorithm\string.hpp>
#include <boost\format.hpp>

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

void
BaseModuleItemsFixture::checkCorrectImport( 
		std::string const & _actual
	,	Lines const & _expected 
)
{
	static boost::format msg( "Import mistmatch\n expected:\t %1%\n actual:\t %2%" );

	std::string expected;

	const int beginLine = _expected.first - 1;
	const int endLine = _expected.second - 1;
	for( int i = beginLine; i <= endLine; ++i )
		expected += m_lines[ i ];

	if( _actual != expected )
		FAIL( ( msg % expected % _actual ).str() );
}

/***************************************************************************/

void 
BaseModuleItemsFixture::runImport( std::string const & _code )
{
	std::stringstream sourceStream( _code );
	std::string target;

	while( std::getline( sourceStream, target, '\n' ) )
	{
		boost::trim( target );
		m_lines.push_back( target );
		target.clear();
	}

	BaseFixture::runImport( _code );
}

/***************************************************************************/

}
