#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_port_importer.hpp"

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

struct PortImporter::PortDeclarationInfoExtractror 
	: public BaseImporter
{

/***************************************************************************/

	typedef
		std::pair< std::string, VlogDM::Location >
		PortItem;

	typedef
		std::vector< PortItem >
		Ports;

/***************************************************************************/

	PortDeclarationInfoExtractror( VlogDM::IAccessor & _accessor )
		:	BaseImporter( _accessor )
		,	m_netType( VlogDM::NetType::Type::wire )
	{
	}

/***************************************************************************/

	template< typename _TDeclarationContext >
	void extract( _TDeclarationContext const & _context )
	{
		static const std::string regKeyWord = "reg";

		forEachChildContext(
				_context
			,	[ & ]( antlr4::tree::ParseTree & _tree )
				{
					if( _tree.getText() == regKeyWord )
						m_netType = VlogDM::NetType::Type::reg;
		
					_tree.accept( this );
				}
		);
	}

/***************************************************************************/

	antlrcpp::Any 
	visitNet_type( Verilog2001Parser::Net_typeContext *ctx ) override 
	{
		VlogDM::NetType::Type type = VlogDM::NetType::fromString( ctx->getText().c_str() );

		return antlrcpp::Any();
	}

/***************************************************************************/

	antlrcpp::Any
	visitRange(Verilog2001Parser::RangeContext *ctx) override 
	{
		VlogDM::Location const location = createLocation( *ctx );

		m_leftBound.emplace( ctx->children[ 1 ]->getText(), location );

		m_rightBound.emplace( ctx->children[ 3 ]->getText(), location );

		return antlrcpp::Any();
	}

/***************************************************************************/

	antlrcpp::Any 
	visitList_of_port_identifiers(Verilog2001Parser::List_of_port_identifiersContext *ctx) override 
	{
		acceptEachChildContext( *ctx );
		
		return antlrcpp::Any();
	}

/***************************************************************************/

	antlrcpp::Any 
	visitPort_identifier(Verilog2001Parser::Port_identifierContext *ctx) override 
	{
		m_portIds.emplace_back( ctx->getText(), createLocation( *ctx ) );

		return antlrcpp::Any();
	}

/***************************************************************************/

	Ports m_portIds;

	boost::optional< PortItem > m_leftBound;

	boost::optional< PortItem > m_rightBound;

	VlogDM::NetType::Type m_netType;

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
PortImporter::importPorts( Verilog2001Parser::Port_declarationContext & _ctx )
{	
	_ctx.accept( this );

	for( auto & value : m_extractedDeclarations )
		m_targetUnit.addDeclaration( std::move( value ) );
}

/***************************************************************************/

void 
PortImporter::importPorts( const Verilog2001Parser::List_of_port_declarationsContext & _ctx )
{
	acceptEachChildContext( _ctx );

	for( auto & value : m_extractedDeclarations )
		m_targetUnit.addDeclaration( std::move( value ) );
}

/***************************************************************************/

antlrcpp::Any
PortImporter::visitList_of_port_declarations( Verilog2001Parser::List_of_port_declarationsContext * ctx )
{
	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
PortImporter::visitPort_declaration( Verilog2001Parser::Port_declarationContext * ctx )
{
	forEachChildContext(
			*ctx
		,	[ & ]( antlr4::tree::ParseTree & _tree )
			{
				VlogDM::Location location = createLocation( *ctx );

				m_extractedDeclarations.emplace_back(
					std::move( getVlogDataModel().getDeclarationFactory().newPortDeclaration( location ) )
				);

				_tree.accept( this );
			}
	);

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

	for( auto const& port : extractor.m_portIds )
		lastDeclaration.addDeclared(
			std::move( 
				declaredFactory.newPort(
						lastDeclaration
					,	port.first
					,	port.second
					,	_direction
					,	extractor.m_netType
					,	std::move( createDimension( extractor ) )
				)
			)
		);
}

/***************************************************************************/

std::unique_ptr< VlogDM::Dimension > 
PortImporter::createDimension(
	PortImporter::PortDeclarationInfoExtractror const& _extractor
)
{
	using namespace VlogDM;

	IAccessor & vlogDm = getVlogDataModel();

	Writable::ExpressionFactory const& expressionFactory
		=	vlogDm.getExpressionFactory();

	Writable::ItemsFactory const& itemsFactory
		=	vlogDm.getItemsFactory();

	auto rangeBoundCreator 
		=	[ & ]( PortDeclarationInfoExtractror::PortItem const& _item ) -> std::unique_ptr< PrimaryLiteral >
			{
				return
					std::move(
						expressionFactory.newPrimaryLiteral(
								_item.second
							,	_item.first
						)
					);
			};

	if(
			_extractor.m_rightBound.is_initialized()
		&&	_extractor.m_leftBound.is_initialized()
	)
	{
		std::unique_ptr< Range > range
			=	itemsFactory.newPartSelectRange(
						_extractor.m_leftBound->second
					,	std::move( rangeBoundCreator( *_extractor.m_leftBound ) )
					,	std::move( rangeBoundCreator( *_extractor.m_rightBound ) )
				);

		return
			std::move(
				itemsFactory.newPackedDimension(
						_extractor.m_leftBound->second
					,	std::move( range )
				)
			);
	}

	return std::unique_ptr< VlogDM::Dimension >();
}

/***************************************************************************/

}
}
