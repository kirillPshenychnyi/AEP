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
	static boost::format linesMistmatch( 
		"Import mistmatch at line %1%\n expected:\t %2%\n actual:\t %3%" 
	);

	static boost::format linesCountMistmatch( 
		"Lines count mistmatch\n expected:\t %1%\n actual:\t %2%"
	);

	CodeLines splitedLines;
	
	boost::split( splitedLines, _actual, [ ]( char c ) { return c == '\n'; } );
	std::for_each( 
			splitedLines.begin()
		,	splitedLines.end()
		,	[] ( std::string & _line ) 
			{
				boost::trim( _line );
			}
	);

	const int beginLine = _expected.first - 1;
	const int endLine = _expected.second - 1;
	
	const int expectedLinesCount = endLine - beginLine + 1;
	const int actualLinesCount = splitedLines.size();

	if( expectedLinesCount != actualLinesCount )
		FAIL( ( linesCountMistmatch % expectedLinesCount % actualLinesCount ).str() );

	for( int i = beginLine, j = 0; i <= endLine; ++i, ++j )
	{
		if( m_lines[ i ] != splitedLines[ j ] )
			FAIL( ( linesMistmatch % i % m_lines[ i ] % splitedLines[ j ] ).str() );
	}
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
