
#include "stdafx.h"

#include "antlr4-runtime.h"
#include "ANTLRGenerated\Verilog2001Parser.h"
#include "ANTLRGenerated\Verilog2001Lexer.h"
#include "ANTLRGenerated\Verilog2001Visitor.h"

#include "vlog_data_model\api\vlog_dm_declaration.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\sources\model\vlog_dm_accessor.hpp"

#include "entry_controller\vlog_import\ec_vlog_design_unit_importer.hpp"

int main()
{
	std::string code = 
		"module top (input wire [2:0] a);	\n"
		"//input a;			\n"
		"wire hello;		\n"	
		"NOT u1(hello, a);	\n"
		"endmodule			\n"
	;

	std::unique_ptr< VlogDM::IAccessor > accessor( new VlogDM::Accessor() );

	antlr4::ANTLRInputStream stream( code );

	Verilog2001Lexer lexer(&stream);

	antlr4::CommonTokenStream tokens(&lexer);

	Verilog2001Parser parser(&tokens);

	antlr4::tree::ParseTree * tree = parser.source_text();

	EntryController::VlogImport::DesingUnitImporter importer( *accessor );

	tree->accept( &importer );

	return 0;
}