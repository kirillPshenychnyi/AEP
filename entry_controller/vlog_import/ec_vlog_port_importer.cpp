#include "stdafx.h"

#include "entry_controller\vlog_import\ec_vlog_port_importer.hpp"

#include "vlog_data_model\api\vlog_dm_net_type.hpp"
#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_port_declaration.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

#include <boost/lexical_cast.hpp>

#include <vector>

/***************************************************************************/

namespace EntryController{
namespace VlogImport{

/***************************************************************************/

struct PortImporter::PortDeclarationInfoExtractror : public BaseImporter
{

/***************************************************************************/

	typedef
		std::pair< std::string, VlogDM::Location >
		Port;

	typedef
		std::vector< Port >
		Ports;

/***************************************************************************/

	PortDeclarationInfoExtractror( VlogDM::IAccessor & _accessor )
		:	BaseImporter( _accessor )
		,	m_netType( VlogDM::NetType::Type::wire )
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
			m_portIds.emplace_back( child->getText(), createLocation( *ctx ) );

		return antlrcpp::Any();
	}

/***************************************************************************/

	Ports m_portIds;
	
	VlogDM::NetType::Type m_netType;

	int m_leftBound;

	int m_rightBound;

/***************************************************************************/

};

/***************************************************************************/

PortImporter::PortImporter(
		VlogDM::IAccessor & _accessor
	,	VlogDM::Writable::DesignUnit & _targetUnit 
	)
	:	BaseImporter( _accessor )
	,	m_targetUnit( _targetUnit )
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

	for( auto & value : m_extractedDeclarations )
		m_targetUnit.addDeclaration( std::move( value ) );

	int i = 0;
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

		m_extractedDeclarations.emplace_back(
			std::move( getVlogDataModel().getDeclarationFactory().newPortDeclaration( location ) )
		);

		child->accept( this );
	}

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
PortImporter::visitInout_declaration( Verilog2001Parser::Inout_declarationContext * ctx )
{
	importPorts( *ctx, VlogDM::PortDirection::Direction::Inout );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
PortImporter::visitInput_declaration( Verilog2001Parser::Input_declarationContext * ctx )
{
	importPorts( *ctx, VlogDM::PortDirection::Direction::Input );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
PortImporter::visitOutput_declaration( Verilog2001Parser::Output_declarationContext * ctx )
{
	importPorts( *ctx, VlogDM::PortDirection::Direction::Output );
	
	return antlrcpp::Any();
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

	PortDeclarationInfoExtractror extractor( getVlogDataModel() );
	extractor.extract( _context );
	
	Writable::PortDeclaration & lastDeclaration 
		= *m_extractedDeclarations.back();
	
	Writable::DeclaredFactory const& declaredFactory 
		=	getVlogDataModel().getDeclaredFactory();

	Writable::ExpressionFactory const& expressionFactory
		=	getVlogDataModel().getExpressionFactory();

	Writable::ItemsFactory const& itemsFactory
		=	getVlogDataModel().getItemsFactory();

	auto rangeBoundCreator 
		=	[ & ]( double _value ) -> std::unique_ptr< PrimaryLiteral >
			{
				return
					std::move(
						expressionFactory.newPrimaryLiteral(
								createLocation( _context )
							,	extractor.m_leftBound
						)
					);
			};

	std::unique_ptr< Dimension > portDimension;

	if(
			extractor.m_rightBound != 0
		||	extractor.m_leftBound != 0
	)
	{
		std::unique_ptr< Range > range
			=	itemsFactory.newExpressionRange(
						createLocation( _context )
					,	std::move( rangeBoundCreator( extractor.m_leftBound ) )
					,	std::move( rangeBoundCreator( extractor.m_rightBound ) )
				);

		portDimension =
			std::move(
					itemsFactory.newPackedDimension( createLocation( _context )
				,	std::move( range ) )
			);
	}

	for( auto const& port : extractor.m_portIds )
		lastDeclaration.addDeclared(
			std::move( 
				declaredFactory.newPort(
						lastDeclaration
					,	port.first
					,	port.second
					,	_direction
					,	std::move( portDimension )
				)
			)
		);
}

/***************************************************************************/

}
}
