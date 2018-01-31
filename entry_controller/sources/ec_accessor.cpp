#include "stdafx.h"

#include "antlr4-runtime.h"
#include "ANTLRGenerated\Verilog2001Parser.h"
#include "ANTLRGenerated\Verilog2001Lexer.h"
#include "ANTLRGenerated\Verilog2001Visitor.h"

#include "entry_controller\sources\ec_accessor.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_design_unit_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"

/***************************************************************************/

namespace EntryController {

/***************************************************************************/

Accessor::Accessor( const std::shared_ptr< VlogDM::IAccessor > & _vlogDm )
	:	m_vlogDm( _vlogDm )
{

}

/***************************************************************************/

void 
Accessor::importVerilog( std::string const & _code )
{
	m_vlogDm->reset();

	antlr4::ANTLRInputStream stream( _code );

	Verilog2001Lexer lexer( &stream );

	antlr4::CommonTokenStream tokens( &lexer );

	Verilog2001Parser parser( &tokens );

	antlr4::tree::ParseTree * tree = parser.source_text();

	EntryController::VlogImport::DesingUnitImporter importer( *m_vlogDm );

	tree->accept( &importer );
}

/***************************************************************************/

}

/***************************************************************************/