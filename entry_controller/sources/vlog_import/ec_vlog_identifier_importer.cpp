#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_range_importer.hpp"
#include "entry_controller\sources\errors\ec_errors_factory.hpp"
#include "entry_controller\api\errors\ec_iundeclared_identifier_error.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_multidimensional_range.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

/***************************************************************************/

namespace EntryController { 
namespace VlogImport { 

/***************************************************************************/

template< typename _IdContext >
void
IdentifierImporter::importIds( _IdContext & _ctx )
{
	visitEachChildContext( _ctx );
}

/***************************************************************************/

void 
IdentifierImporter::importId( 
	Verilog2001Parser::Simple_hierarchical_identifierContext const & _ctx 
)
{
	_ctx.children.front()->accept( this );
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
IdentifierImporter::visitRange_expression( 
	Verilog2001Parser::Range_expressionContext * ctx 
)
{
	RangeImporter rangeImporter( takeVlogDataModel(), takeErrorsSet() );

	m_currentRanges.push_back( rangeImporter.importRange( *ctx ) );

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::createSimpleId( antlr4::ParserRuleContext & _ctx )
{
	if( _ctx.children.empty() )
		RETURN_ANY

	std::string const identifier = _ctx.children.front()->getText();
	
	auto declared 
		=	takeVlogDataModel().getCurrentImportedUnit().findDeclared( 
				identifier
			);

	if( !declared )
	{
		addError( Errors::ErrorsFactory::newUndeclaredIdentifierError( _ctx ) );
		RETURN_ANY;
	}

	VlogDM::Writable::ObjectFactory const & objectFactory
		= takeVlogDataModel().getObjectFactory();

	m_extractedIds.push_back(
		objectFactory.getItemsFactory().newIdentifier( 
				createLocation( _ctx )
			,	*declared 
			,	createRange()
		)
	);

	m_currentRanges.clear();

	RETURN_ANY
}

/***************************************************************************/

VlogDM::RangePtr 
IdentifierImporter::createRange()
{
	if( m_currentRanges.empty() )
		return VlogDM::RangePtr();

	if( m_currentRanges.size() == 1 )
		return std::move( m_currentRanges.front() );

	VlogDM::Writable::ObjectFactory const & objectFactory
		= takeVlogDataModel().getObjectFactory();

	auto multidimRange = 
		objectFactory.getItemsFactory().newMultidimensionalRange( 
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


template
void
IdentifierImporter::importIds< Verilog2001Parser::Net_assignmentContext >
( Verilog2001Parser::Net_assignmentContext & _ctx );

/***************************************************************************/

template
void
IdentifierImporter::importIds< Verilog2001Parser::Variable_lvalueContext >
( Verilog2001Parser::Variable_lvalueContext & _ctx );

/***************************************************************************/

}
}

/***************************************************************************/