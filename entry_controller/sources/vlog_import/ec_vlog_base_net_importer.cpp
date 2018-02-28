#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_base_net_importer.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_net_extractor.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_declared.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declaration.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

template< typename _Declaration >
BaseNetImporter< _Declaration >::BaseNetImporter( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
{
}

/***************************************************************************/

template< typename _Declaration >
void 
BaseNetImporter< _Declaration >::addDeclareds( 
		antlr4::ParserRuleContext & _context
	,	DeclaredCreator _creator
	)
{
	using namespace VlogDM;

	NetExtractor extractor( getVlogDataModel() );
	extractor.extract( _context );
	
	DeclarationPtr declaration 
		=	createDeclaration( 
				createLocation( _context )
			,	std::move( extractor.m_type ) 
			);
	
	int dimensionIdx = 0;
	for( auto const& port : extractor.m_netIds )
	{
		declaration->addDeclared(
			_creator(
					*declaration
				,	extractor.getDimension( dimensionIdx++ )
				,	port
			)
		);
	}

	m_extractedDeclarations.push_back( std::move( declaration ) );
}

/***************************************************************************/

template< typename _Declaration >
void 
BaseNetImporter< _Declaration >::addDeclarations()
{
	for( auto & value : m_extractedDeclarations )
	{
		getVlogDataModel().getCurrentImportedUnit().addDeclaration(
			std::move( value )
		);
	}
}

/***************************************************************************/

template class BaseNetImporter< VlogDM::Writable::PortDeclaration >;

template class BaseNetImporter< VlogDM::Writable::VariableDeclaration >;

/***************************************************************************/

}
}