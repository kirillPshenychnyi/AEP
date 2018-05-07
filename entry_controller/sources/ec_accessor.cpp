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

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "aep\api\aep_iaccessor.hpp"

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

	antlr4::ANTLRInputStream stream( _code );

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
		Aep::IAccessor::GlobalClockParameters & _clockParams
	,	boost::optional< Aep::IAccessor::GlobalResetParameters const & > _resetParams
)
{
	m_aepAccessor.runEngine( _clockParams, _resetParams );
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
}

/***************************************************************************/

}

/***************************************************************************/