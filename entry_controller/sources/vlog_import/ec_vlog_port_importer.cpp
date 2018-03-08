#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_port_importer.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_type.hpp"
#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_port_declaration.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"

#include <boost/lexical_cast.hpp>

#include <vector>

/***************************************************************************/

namespace EntryController{
namespace VlogImport{

/***************************************************************************/

PortImporter::PortImporter( VlogDM::IAccessor & _accessor )
	:	BaseClass( _accessor )
{
}

/***************************************************************************/

void 
PortImporter::importPorts( Verilog2001Parser::Port_declarationContext & _ctx )
{	
	_ctx.accept( this );

	addDeclarations();
}

/***************************************************************************/

void 
PortImporter::importPorts( const Verilog2001Parser::List_of_port_declarationsContext & _ctx )
{
	visitEachChildContext( _ctx );

	addDeclarations();
}

/***************************************************************************/

antlrcpp::Any 
PortImporter::visitInout_declaration( Verilog2001Parser::Inout_declarationContext * ctx )
{
	importPorts( *ctx, VlogDM::PortDirection::Direction::Inout );

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any 
PortImporter::visitInput_declaration( Verilog2001Parser::Input_declarationContext * ctx )
{
	importPorts( *ctx, VlogDM::PortDirection::Direction::Input );

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any
PortImporter::visitOutput_declaration( Verilog2001Parser::Output_declarationContext * ctx )
{
	importPorts( *ctx, VlogDM::PortDirection::Direction::Output );
	
	RETURN_ANY
}

/***************************************************************************/

template< typename _PortDeclarationContext >
void 
PortImporter::importPorts(
		_PortDeclarationContext & _context
	,	VlogDM::PortDirection::Direction _direction
)
{
	using namespace VlogDM;

	Writable::ObjectFactory const & objectFactory
		= getVlogDataModel().getObjectFactory();

	Writable::DeclaredFactory const& declaredFactory 
		=	objectFactory.getDeclaredFactory();

	addDeclareds( 
			_context 
		,	[ & ]( 
					Declaration & _declaration
				,	DimensionPtr _dimension
				,	NetExtractor::NetItem _portItem
			)
			{
				return
					declaredFactory.newPort(
							_declaration
						,	_portItem.first
						,	_portItem.second
						,	_direction
						,	std::move( _dimension )
					);
			}
	);
}

/***************************************************************************/

VlogDM::Writable::PortDeclarationPtr
PortImporter::createDeclaration( 
		VlogDM::Location const & _location
	,	VlogDM::TypePtr _type 
	) 
{
	VlogDM::Writable::ObjectFactory const & objectFactory
		= getVlogDataModel().getObjectFactory();
	
	return 
		objectFactory.getDeclarationFactory().newPortDeclaration( 
				_location
			,	std::move( _type ) 
		);
}

/***************************************************************************/

}
}
