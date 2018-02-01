#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_net_extractor.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

NetExtractor::NetExtractor( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
	,	m_netType( VlogDM::NetKind::Kind::wire )
	,	m_isReg( false )
{
}

/***************************************************************************/

void
NetExtractor::extract( antlr4::ParserRuleContext const & _context )
{
	static const std::string regKeyWord = "reg";

	forEachChildContext(
		_context
	,	[ & ]( antlr4::tree::ParseTree & _tree )
		{
			if( _tree.getText() == regKeyWord )
				m_isReg = true;

			_tree.accept( this );
		}
	);
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitNet_type( Verilog2001Parser::Net_typeContext *ctx )
{
	m_netType = VlogDM::NetKind::fromString( ctx->getText().c_str() );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitRange( Verilog2001Parser::RangeContext *ctx )
{
	VlogDM::Location const location = createLocation( *ctx );

	m_leftBound.emplace( ctx->children[ 1 ]->getText(), location );

	m_rightBound.emplace( ctx->children[ 3 ]->getText(), location );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitList_of_port_identifiers(
	Verilog2001Parser::List_of_port_identifiersContext *ctx
)
{
	return visitListOfIds( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
NetExtractor::visitList_of_net_identifiers(
		Verilog2001Parser::List_of_net_identifiersContext *ctx
) 
{
	return visitListOfIds( *ctx );
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitPort_identifier( Verilog2001Parser::Port_identifierContext *ctx )
{
	return extractId( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
NetExtractor::visitNet_identifier(
		Verilog2001Parser::Net_identifierContext *ctx
	)
{
	return extractId( *ctx );
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitListOfIds( antlr4::ParserRuleContext & _context )
{
	acceptEachChildContext( _context );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
NetExtractor::extractId( antlr4::ParserRuleContext & _context )
{
	m_netIds.emplace_back( _context.getText(), createLocation( _context ) );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}