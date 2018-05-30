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
DataflowProcessImporter::visitNet_assignment(
	Verilog2001Parser::Net_assignmentContext * ctx
)
{
	using namespace VlogDM;

	IdentifierImporter idImporter( takeVlogDataModel(), takeErrorsSet() );

	ctx->net_lvalue()->accept( &idImporter );
	
	m_targetExpression 
		=	ExpressionImporter::createExpressionFromIds(
					idImporter
				,	takeVlogDataModel().getObjectFactory().getExpressionFactory()
				,	createLocation( *ctx )
			);

	ctx->expression()->accept( this );
	
	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
DataflowProcessImporter::visitExpression( Verilog2001Parser::ExpressionContext * ctx )
{
	using namespace VlogDM;

	IAccessor & vlogDm = takeVlogDataModel();

	Writable::ObjectFactory const & objectFactory = vlogDm.getObjectFactory();

	ExpressionImporter expressionImporter( takeVlogDataModel(), takeErrorsSet() );

	auto process = objectFactory.getItemsFactory().newContinuousAssignment( 
							m_processLocation 
						,	objectFactory.getExpressionFactory().newBinaryOperator(
									std::move( m_targetExpression )
								,	expressionImporter.importExpression( *ctx )
								,	Operator::Kind::Assign
							)
					);

	vlogDm.getCurrentImportedUnit().addProcess( std::move( process ) );

	RETURN_ANY
}

/***************************************************************************/

}
}
