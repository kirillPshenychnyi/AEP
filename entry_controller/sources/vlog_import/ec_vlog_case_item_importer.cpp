#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_case_item_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_statement_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_statement_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_case_item.hpp"

#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_statement.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

CaseItemImporter::CaseItemImporter( VlogDM::IAccessor & _vlogDm )
	:	BaseImporter( _vlogDm )
{
}

/***************************************************************************/

VlogDM::BaseCaseItemPtr 
CaseItemImporter::importCaseItem( Verilog2001Parser::Case_itemContext & _caseItem )
{
	using namespace VlogDM;

	StatementImporter statementImporter( getVlogDataModel() );
	
	if( auto defaultItem = _caseItem.default_case_item() )
	{
		statementImporter.importStatement( *defaultItem->statement_or_null() );

		Writable::DefaultCaseItemPtr defaultCaseItem
			=	getVlogDataModel().getObjectFactory().getItemsFactory().newDefaultCaseItem( 
					createLocation( _caseItem ) 
				);

		defaultCaseItem->setStatement( statementImporter.takeStatement() );

		return std::move( defaultCaseItem );
	}

	auto const & expressions = _caseItem.expression();
	
	Writable::CaseItemPtr caseItem
		=	getVlogDataModel().getObjectFactory().getItemsFactory().newCaseItem( 
				createLocation( _caseItem ) 
			);


	ExpressionImporter exprImporter( getVlogDataModel() );
	
	const int nExpressions = expressions.size();
	for( int i = 0; i < nExpressions; ++i )
		caseItem->addExpression( exprImporter.importExpression( *expressions[ i ] ) );

	statementImporter.importStatement( *_caseItem.statement_or_null() );
	caseItem->setStatement( statementImporter.takeStatement() );

	return std::move( caseItem );
}

/***************************************************************************/

}
}