#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_variable_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_variable.hpp"
#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_variable_declaration.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

void
VariableImporter::importVars( Verilog2001Parser::Net_declarationContext & _ctx )
{
	importVar( _ctx );

	addDeclarations();
}

/***************************************************************************/

void 
VariableImporter::importVars( Verilog2001Parser::Reg_declarationContext & _ctx )
{
	importVar( _ctx );

	addDeclarations();
}

/***************************************************************************/

template < typename _Context >
void
VariableImporter::importVar( _Context & _ctx )
{
	using namespace VlogDM;

	Writable::DeclaredFactory const& declaredFactory 
		=	takeVlogDataModel().getObjectFactory().getDeclaredFactory();

	addDeclareds(
			_ctx
		,	[ & ]( 
					Declaration & _declaration
				,	DimensionPtr _dimension
				,	NetExtractor::NetItem _portItem
			)
			{
				return 
					declaredFactory.newVariable(
							_declaration
						,	_portItem.first
						,	_portItem.second
						,	false
						,	std::move( _dimension )
					);
			}
	);
}

/***************************************************************************/

VlogDM::Writable::VariableDeclarationPtr 
VariableImporter::createDeclaration(
		VlogDM::Location const & _location
	,	VlogDM::TypePtr _type
	)
{
	VlogDM::Writable::ObjectFactory const & objectFactory
		= takeVlogDataModel().getObjectFactory();

	return 
		objectFactory.getDeclarationFactory().newVariableDeclaration( 
				_location
			,	std::move( _type )
		);
}

/***************************************************************************/

}
}