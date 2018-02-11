#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

ExpressionImporter::ExpressionImporter( 
		VlogDM::IAccessor & _vlogDm 
	,	VlogDM::Writable::DesignUnit const & _targetUnit
	)
	:	BaseImporter( _vlogDm )
	,	m_targetUnit( _targetUnit )
{
}

/***************************************************************************/

VlogDM::ExpressionPtr
ExpressionImporter::importExpression( Verilog2001Parser::ExpressionContext & _expression )
{
	acceptEachChildContext( _expression );

	if( m_primes.size() == 1 )
		return std::move( m_primes.front() );

	return VlogDM::ExpressionPtr();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitTerm( Verilog2001Parser::TermContext * ctx )
{
	acceptEachChildContext( *ctx );
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitPrimary( Verilog2001Parser::PrimaryContext * ctx )
{
	acceptEachChildContext( *ctx );
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
ExpressionImporter::visitSimple_hierarchical_identifier( 
	Verilog2001Parser::Simple_hierarchical_identifierContext * ctx 
	)
{
	using namespace VlogDM;

	IAccessor & vlogDM = getVlogDataModel();

	auto declared = m_targetUnit.findDeclared( ctx->getText() );

	IdentifierImporter idImporter( getVlogDataModel(), m_targetUnit );

	idImporter.importId( *ctx );

	auto expression = 
			vlogDM.getExpressionFactory().newPrimaryIdentifier( 
					idImporter.takeId( 0 )
			);

	m_primes.push_back( std::move( expression ) );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}