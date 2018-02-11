#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"

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
IdentifierImporter::importIds( 
		Verilog2001Parser::List_of_net_assignmentsContext & _ctx 
	)
{
	acceptEachChildContext( _ctx );
}

/***************************************************************************/

void 
IdentifierImporter::importId( 
		Verilog2001Parser::Simple_hierarchical_identifierContext & _ctx 
	)
{
	createSimpleId( _ctx );
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::visitNet_lvalue( Verilog2001Parser::Net_lvalueContext * ctx )
{
	return createSimpleId( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
IdentifierImporter::createSimpleId( antlr4::ParserRuleContext & _ctx )
{
	auto declared = m_targetUnit.findDeclared( _ctx.getText() );
	
	m_extractedIds.push_back(
		getVlogDataModel().getItemsFactory().newIdentifier( 
				createLocation( _ctx )
			,	*declared 
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