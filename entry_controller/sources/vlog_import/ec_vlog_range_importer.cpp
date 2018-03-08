#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_range_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_expression_importer.hpp"

#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

RangeImporter::RangeImporter( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
{
}

/***************************************************************************/

VlogDM::RangePtr 
RangeImporter::importRange( 
	Verilog2001Parser::Range_expressionContext & _rangeExpression 
)
{
	visitEachChildContext( _rangeExpression );

	assert( m_lsbExpression );

	VlogDM::Writable::ItemsFactory const & itemsFactory
		=	getVlogDataModel().getObjectFactory().getItemsFactory();

	return 
		m_msbExpression 
		?	itemsFactory.newPartSelectRange(
					createLocation( _rangeExpression )
				,	std::move( m_lsbExpression )
				,	std::move( m_msbExpression )
			)
		:	itemsFactory.newExpressionRange( 
				std::move( m_lsbExpression )
			);
}

/***************************************************************************/

antlrcpp::Any 
RangeImporter::visitExpression( Verilog2001Parser::ExpressionContext * ctx )
{
	ExpressionImporter expressionImporter ( getVlogDataModel() );
	
	auto bitSelect = expressionImporter.importExpression( *ctx );

	if( !m_lsbExpression )
		m_lsbExpression = std::move( bitSelect );
	else
		m_msbExpression = std::move( bitSelect );

	RETURN_ANY
}

/***************************************************************************/

}
}