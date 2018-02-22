#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

/***************************************************************************/

namespace EntryController { 
namespace VlogImport { 

/***************************************************************************/

IdentifierImporter::IdentifierImporter( 
		VlogDM::IAccessor & _accessor
	,	VlogDM::Writable::DesignUnit const & _targetUnit 
	)
	:	BaseImporter( _accessor )
	,	m_targetUnit( _targetUnit )
{
}

/***************************************************************************/

void 
IdentifierImporter::importIds(  Verilog2001Parser::Net_assignmentContext & _ctx )
{
	acceptEachChildContext( _ctx );
}

/***************************************************************************/

void 
IdentifierImporter::importId( 
		Verilog2001Parser::Simple_hierarchical_identifierContext & _ctx 
	)
{
	_ctx.children.front()->accept( this );
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::visitNet_lvalue( Verilog2001Parser::Net_lvalueContext * ctx )
{	
	acceptEachChildContext( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::visitNet_concatenation( 
	Verilog2001Parser::Net_concatenationContext * ctx 
)
{
	acceptEachChildContext( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::visitNet_concatenation_value(
	Verilog2001Parser::Net_concatenation_valueContext * ctx
)
{
	acceptEachChildContext( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
IdentifierImporter::visitSimple_hierarchical_branch(
	Verilog2001Parser::Simple_hierarchical_branchContext * ctx
)
{
	acceptEachChildContext( *ctx );
	return createSimpleId( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::visitRange_expression( Verilog2001Parser::Range_expressionContext  * ctx )
{
	ExpressionImporter expressionImporter( getVlogDataModel(), m_targetUnit );

	m_range = expressionImporter.importRange( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::createSimpleId( antlr4::ParserRuleContext & _ctx )
{
	auto declared = m_targetUnit.findDeclared( _ctx.children.front()->getText() );

	m_extractedIds.push_back(
		getVlogDataModel().getItemsFactory().newIdentifier( 
				createLocation( _ctx )
			,	*declared 
			,	std::move( m_range )
		)
	);

	return antlrcpp::Any();
}

/***************************************************************************/

VlogDM::BaseIdentifierPtr 
IdentifierImporter::takeId( int _idx )
{
	return std::move( m_extractedIds[ _idx ] );
}

/***************************************************************************/

int 
IdentifierImporter::getIdsCount() const
{
	return m_extractedIds.size();
}

/***************************************************************************/

}
}

/***************************************************************************/