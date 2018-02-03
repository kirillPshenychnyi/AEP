#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_variable_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_variable.hpp"
#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_variable_declaration.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

VariableImporter::VariableImporter(
			VlogDM::IAccessor & _accessor
		,	VlogDM::Writable::DesignUnit & _targetUnit 
	)
	:	BaseClass( _accessor, _targetUnit )
{
}

/***************************************************************************/

void
VariableImporter::importVars( Verilog2001Parser::Net_declarationContext & _ctx )
{
	_ctx.accept( this );
}

/***************************************************************************/

antlrcpp::Any 
VariableImporter::visitNet_declaration( 
		Verilog2001Parser::Net_declarationContext * ctx 
	)
{
	using namespace VlogDM;

	Location location = createLocation( *ctx );

	IAccessor & vlog = getVlogDataModel();

	m_extractedDeclarations.emplace_back(
			vlog.getDeclarationFactory().newVariableDeclaration( 
				location 
			)
	);
	
	Writable::DeclaredFactory const& declaredFactory 
		=	getVlogDataModel().getDeclaredFactory();

	addDeclareds(
			*ctx
		,	[ & ]( 
					Declaration & _declaration
				,	TypePtr _type
				,	DimensionPtr _dimension
				,	NetExtractor::NetItem _portItem
			)
			{
				return 
					declaredFactory.newVariable(
							_declaration
						,	std::move( _type )
						,	_portItem.first
						,	_portItem.second
						,	false
						,	std::move( _dimension )
					);
			}
	);

	return antlrcpp::Any();
}

/***************************************************************************/

}
}