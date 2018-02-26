#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_range_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_multidimensional_range.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

/***************************************************************************/

namespace EntryController { 
namespace VlogImport { 

/***************************************************************************/

IdentifierImporter::IdentifierImporter( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
{
}

/***************************************************************************/

void 
IdentifierImporter::importIds(  Verilog2001Parser::Net_assignmentContext & _ctx )
{
	visitEachChildContext( _ctx );
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
	visitEachChildContext( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::visitNet_concatenation( 
	Verilog2001Parser::Net_concatenationContext * ctx 
)
{
	visitEachChildContext( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::visitNet_concatenation_value(
	Verilog2001Parser::Net_concatenation_valueContext * ctx
)
{
	visitEachChildContext( *ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
IdentifierImporter::visitSimple_hierarchical_branch(
	Verilog2001Parser::Simple_hierarchical_branchContext * ctx
)
{
	visitEachChildContext( *ctx );
	return createSimpleId( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::visitRange_expression( Verilog2001Parser::Range_expressionContext * ctx )
{
	RangeImporter rangeImporter( getVlogDataModel() );

	m_currentRanges.push_back( rangeImporter.importRange( *ctx ) );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::createSimpleId( antlr4::ParserRuleContext & _ctx )
{
	auto declared 
		=	getVlogDataModel().getCurrentImportedUnit().findDeclared( 
				_ctx.children.front()->getText() 
			);

	assert( declared );

	m_extractedIds.push_back(
		getVlogDataModel().getItemsFactory().newIdentifier( 
				createLocation( _ctx )
			,	*declared 
			,	createRange()
		)
	);

	m_currentRanges.clear();

	return antlrcpp::Any();
}

/***************************************************************************/

VlogDM::RangePtr 
IdentifierImporter::createRange()
{
	const int rangesCount = m_currentRanges.size();

	if( m_currentRanges.empty() )
		return VlogDM::RangePtr();

	if( m_currentRanges.size() == 1 )
		return std::move( m_currentRanges.front() );

	auto multidimRange = 
		getVlogDataModel().getItemsFactory().newMultidimensionalRange( 
			m_currentRanges.front()->getLocation()
		);

	for( auto & range : m_currentRanges )
		multidimRange->addRange( std::move( range ) );

	m_currentRanges.clear();

	return multidimRange;
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