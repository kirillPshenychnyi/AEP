#include "stdafx.h"

#include "entry_controller\vlog_import\ec_vlog_dm_port_importer.hpp"

#include "vlog_data_model\api\vlog_dm_net_type.hpp"
#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_port_declaration.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"

#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declaration.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

#include <boost/lexical_cast.hpp>

#include <vector>

/***************************************************************************/

namespace EntryController{
namespace VlogImport{

/***************************************************************************/

struct PortImporter::PortDeclarationInfoExtractror : public Verilog2001BaseVisitor
{

/***************************************************************************/

	typedef
		std::vector< std::string >
		PortIds;

/***************************************************************************/

	PortDeclarationInfoExtractror()
		:	m_netType( VlogDM::NetType::Type::wire )
		,	m_leftBound( 0 )
		,	m_rightBound( 0 )
	{
	}

/***************************************************************************/

	template< typename _TDeclarationContext >
	void extract( _TDeclarationContext const & _context )
	{
		for( auto child : _context.children )
			child->accept( this );
	}

/***************************************************************************/

	antlrcpp::Any 
	visitNet_type(Verilog2001Parser::Net_typeContext *ctx) override 
	{
		VlogDM::NetType::Type type = VlogDM::NetType::fromString( ctx->getText().c_str() );

		return antlrcpp::Any();
	}

/***************************************************************************/

	antlrcpp::Any
	visitRange(Verilog2001Parser::RangeContext *ctx) override 
	{
		try
		{
			m_leftBound = boost::lexical_cast< int >( ctx->children[ 1 ]->getText() );

			m_rightBound = boost::lexical_cast< int > ( ctx->children[ 3 ]->getText() );

		}
		catch( boost::bad_lexical_cast )
		{
			m_leftBound = 0;
			m_rightBound = 0;
		}

		return antlrcpp::Any();
	}

/***************************************************************************/

	antlrcpp::Any 
	visitList_of_port_identifiers(Verilog2001Parser::List_of_port_identifiersContext *ctx) override 
	{
		for( auto child : ctx->children )
			m_portIds.push_back( child->getText() );

		return antlrcpp::Any();
	}

/***************************************************************************/

	PortIds m_portIds;
	
	VlogDM::NetType::Type m_netType;

	int m_leftBound;

	int m_rightBound;

/***************************************************************************/

};

/***************************************************************************/

PortImporter::PortImporter( VlogDM::IAccessor & _accessor )
	:	BaseImporter( _accessor )
{
}

/***************************************************************************/

void 
PortImporter::importPorts( const Verilog2001Parser::List_of_portsContext & _ctx )
{	
	importPorts< Verilog2001Parser::List_of_portsContext >( _ctx );
}

/***************************************************************************/

void 
PortImporter::importPorts( const Verilog2001Parser::List_of_port_declarationsContext & _ctx )
{
	importPorts< Verilog2001Parser::List_of_port_declarationsContext >( _ctx );
}

/***************************************************************************/

template< typename _PortListContext >
void 
PortImporter::importPorts( const _PortListContext & _list )
{
	for( auto child : _list.children )
		child->accept( this );
}

/***************************************************************************/

antlrcpp::Any
PortImporter::visitList_of_port_declarations( Verilog2001Parser::List_of_port_declarationsContext * ctx )
{
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
PortImporter::visitPort( Verilog2001Parser::PortContext * ctx )
{
	std::string text = ctx->getText();
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
PortImporter::visitPort_declaration( Verilog2001Parser::Port_declarationContext * ctx )
{
	for( auto child : ctx->children )
	{
		VlogDM::Location location = createLocation( *ctx );

		PortDeclarationPtr portDecl
			= getVlogDataModel().getDeclarationFactory().newPortDeclaration( location );

		m_extractedDeclarations.push_back( std::move( portDecl ) );

		child->accept( this );
	}

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
PortImporter::visitInout_declaration( Verilog2001Parser::Inout_declarationContext * ctx )
{
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
PortImporter::visitInput_declaration( Verilog2001Parser::Input_declarationContext * ctx )
{
	using namespace VlogDM;

	PortDeclarationInfoExtractror extractor;
	extractor.extract( *ctx );
	
	Writable::PortDeclaration & lastDeclaration 
		= *m_extractedDeclarations.back();
	
	Writable::DeclaredFactory const & declaredFactory 
		= getVlogDataModel().getDeclaredFactory();

	lastDeclaration.addDeclared(
				std::move( 
					declaredFactory.newPort(
					lastDeclaration
				,	extractor.m_portIds[ 0 ]
				,	createLocation( *ctx )
				,	PortDirection::Direction::Input
				,	nullptr
			)
		)
	);

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
PortImporter::visitOutput_declaration( Verilog2001Parser::Output_declarationContext * ctx )
{
	return antlrcpp::Any();
}

/***************************************************************************/

}
}
