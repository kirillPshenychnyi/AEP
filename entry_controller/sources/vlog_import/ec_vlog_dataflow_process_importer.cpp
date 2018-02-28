#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_dataflow_process_importer.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_identifier_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"

#include "vlog_data_model\api\vlog_dm_operator.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_concatenation.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"

/***************************************************************************/

namespace EntryController{
namespace VlogImport {

/***************************************************************************/

DataflowProcessImporter::DataflowProcessImporter( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
{
}

/***************************************************************************/

void 
DataflowProcessImporter::importProcess( 
		Verilog2001Parser::Continuous_assignContext & _ctx 
	)
{
	m_processLocation = createLocation( _ctx );
	visitEachChildContext( _ctx );
}

/***************************************************************************/

antlrcpp::Any 
DataflowProcessImporter::visitList_of_net_assignments(
		Verilog2001Parser::List_of_net_assignmentsContext * _ctx
	)
{
	visitEachChildContext( *_ctx );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
DataflowProcessImporter::visitNet_assignment(
	Verilog2001Parser::Net_assignmentContext * ctx
)
{
	using namespace VlogDM;

	Writable::ExpressionFactory const & expressionFactory 
			= getVlogDataModel().getObjectFactory().getExpressionFactory();

	IdentifierImporter importer( getVlogDataModel() );

	auto primaryIdCreator
		=	[ & ]( int _idx ) -> ExpressionPtr
			{
				return expressionFactory.newPrimaryIdentifier( importer.takeId( _idx ) );
			};

	// lhs is first child
	ctx->children.front()->accept( &importer );
	
	const int idsCount = importer.getIdsCount();

	if( idsCount == 1 )
	{
		m_targetExpression = primaryIdCreator( 0 );
	}
	else
	{
		auto concat = expressionFactory.newConcatenation( createLocation( *ctx ) );

		for( int i = 0; i < idsCount; ++i )
			concat->addExpression( primaryIdCreator( i ) );

		m_targetExpression = std::move( concat );
	}

	// rhs expression is last child
	ctx->children.back()->accept( this );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
DataflowProcessImporter::visitExpression( Verilog2001Parser::ExpressionContext * ctx )
{
	using namespace VlogDM;

	IAccessor & vlogDm = getVlogDataModel();

	Writable::ObjectFactory const & objectFactory = vlogDm.getObjectFactory();

	ExpressionImporter expressionImporter( getVlogDataModel() );

	auto process = objectFactory.getItemsFactory().newContinuousAssignment( 
							m_processLocation 
						,	objectFactory.getExpressionFactory().newBinaryOperator(
									std::move( m_targetExpression )
								,	expressionImporter.importExpression( *ctx )
								,	Operator::Kind::Assign
							)
					);

	vlogDm.getCurrentImportedUnit().addProcess( std::move( process ) );

	return antlrcpp::Any();
}

/***************************************************************************/

}
}
