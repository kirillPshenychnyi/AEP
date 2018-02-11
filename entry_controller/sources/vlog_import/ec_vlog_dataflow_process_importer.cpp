#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_dataflow_process_importer.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"

#include "vlog_data_model\api\vlog_dm_operator.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"

/***************************************************************************/

namespace EntryController{
namespace VlogImport {

/***************************************************************************/

DataflowProcessImporter::DataflowProcessImporter(
		VlogDM::IAccessor & _accessor 
	,	VlogDM::Writable::DesignUnit & _targetUnit
	)
	:	BaseImporter( _accessor )
	,	m_targetUnit( _targetUnit )
{
}

/***************************************************************************/

void 
DataflowProcessImporter::importProcess( 
		Verilog2001Parser::Continuous_assignContext & _ctx 
	)
{
	m_processLocation = createLocation( _ctx );
	acceptEachChildContext( _ctx );
}

/***************************************************************************/

antlrcpp::Any 
DataflowProcessImporter::visitList_of_net_assignments(
		Verilog2001Parser::List_of_net_assignmentsContext * ctx
	)
{
	using namespace VlogDM;

	Writable::ExpressionFactory const & expressionFactory 
			= getVlogDataModel().getExpressionFactory();

	IdentifierImporter importer( getVlogDataModel(), m_targetUnit );

	importer.importIds( *ctx );

	const int idsCount = importer.getIdsCount();

	if( idsCount == 1 )
	{
		m_targetExpression.reset(
			expressionFactory.newPrimaryIdentifier( importer.takeId( 0 ) ).release()
		);
	}

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
DataflowProcessImporter::visitExpression( Verilog2001Parser::ExpressionContext * ctx )
{
	using namespace VlogDM;

	IAccessor & vlogDm = getVlogDataModel();

	ExpressionImporter expressionImporter( getVlogDataModel(), m_targetUnit );

	auto process = vlogDm.getItemsFactory().newContinuousAssignment( 
							m_processLocation 
						,	vlogDm.getExpressionFactory().newBinaryOperator(
									std::move( m_targetExpression )
								,	expressionImporter.importExpression( *ctx )
								,	Operator::Enum::Assign
							)
					);

	m_targetUnit.addProcess( std::move( process ) );

	return antlrcpp::Any();
}

/***************************************************************************/

VlogDM::ExpressionPtr 
DataflowProcessImporter::getTargetExpression()
{
	using namespace VlogDM;

	IAccessor & vlogDM = getVlogDataModel();

	return VlogDM::ExpressionPtr();
}

/***************************************************************************/

}
}
