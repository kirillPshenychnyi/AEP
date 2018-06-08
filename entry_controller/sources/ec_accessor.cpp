#include "stdafx.h"

#include "antlr4-runtime.h"
#include "ANTLRGenerated\Verilog2001Parser.h"
#include "ANTLRGenerated\Verilog2001Lexer.h"
#include "ANTLRGenerated\Verilog2001Visitor.h"

#include "entry_controller\sources\ec_accessor.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_design_unit_importer.hpp"
#include "entry_controller\sources\errors\ec_parse_error_listener.hpp"
#include "entry_controller\sources\errors\ec_errors_set.hpp"
#include "entry_controller\sources\errors\ec_dump_error_visitor.hpp"
#include "entry_controller\sources\ec_resources.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "aep\api\aep_iaccessor.hpp"

#include <iostream>

/***************************************************************************/

namespace EntryController {

/***************************************************************************/

Accessor::Accessor( 
		const std::shared_ptr< VlogDM::IAccessor > _vlogDm
	,	const std::shared_ptr< Aep::IAccessor > _aepAccessor
	)
	:	m_vlogDm( *_vlogDm )
	,	m_aepAccessor( *_aepAccessor )
	,	m_importErrors( new Errors::ErrorsSet() )
{

}

/***************************************************************************/

bool 
Accessor::importVerilog( std::string const & _code )
{
	reset();

	return runImport( _code, "sample.sv" );
}

/***************************************************************************/

void 
Accessor::addFile( std::string const & _path )
{
	m_designFiles.insert( _path );
}

/***************************************************************************/

bool 
Accessor::runVerilogImport()
{
	std::cout << Resources::LogMessages::StartVerilogImport << std::endl;

	bool importResult = true;

	for( const auto & designFile : m_designFiles )
	{
		std::ifstream stream;
		stream.open( designFile );

		bool isOpen = stream.is_open();

		if( !isOpen )
			throw std::logic_error( "Could not open file " + designFile );

		importResult = runImport( stream, designFile );
	}

	std::cout << 
		( 
			importResult 
			?	Resources::LogMessages::VerilogImportSuccess
			:	Resources::LogMessages::VerilogImportSuccess 
		);

	std::cout << std::endl;

	return importResult;
}

/***************************************************************************/

template< typename _TStream >
bool 
Accessor::runImport( _TStream  & _sourceStream, std::string const & _name )
{
	antlr4::ANTLRInputStream stream( _sourceStream );
	
	stream.name = _name;

	Verilog2001Lexer lexer( &stream );

	antlr4::CommonTokenStream tokens( &lexer );

	Verilog2001Parser parser( &tokens );

	Errors::ParseErrorListener errorListener( *m_importErrors );
	parser.removeErrorListeners();
	parser.addErrorListener( &errorListener );

	antlr4::tree::ParseTree * tree = parser.source_text();

	VlogImport::DesingUnitImporter importer( m_vlogDm, *m_importErrors );

	tree->accept( &importer );

	return !m_importErrors->hasErrors();
}

/***************************************************************************/

void 
Accessor::runAepAnalysis(
		Aep::CheckerIds _checkers
	,	Aep::IAccessor::GlobalClockParameters & _clockParams
	,	boost::optional< Aep::IAccessor::GlobalResetParameters const & > _resetParams
)
{
	m_aepAccessor.runEngine( _checkers, _clockParams, _resetParams );
}

/***************************************************************************/

void 
Accessor::dumpErrors( std::ostream & _output ) const
{
	Errors::DumpErrorVisitor dumpErrors ( _output );

	m_importErrors->forEachError(
		[ & ]( Errors::ImportError const & _error )
		{
			_error.accept( dumpErrors );
		}
	);
}

/***************************************************************************/

void 
Accessor::reset()
{
	m_vlogDm.reset();
	m_importErrors->reset();
	m_designFiles.clear();
}

/***************************************************************************/

}

/***************************************************************************/