#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_net_extractor.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_variable_type.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_type_factory.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

NetExtractor::NetExtractor( VlogDM::IAccessor & _accessor )
	: BaseImporter( _accessor )
	, m_netType( VlogDM::NetKind::Kind::wire )
	, m_isReg( false )
{
}

/***************************************************************************/

void
NetExtractor::extract( antlr4::ParserRuleContext & _context )
{
	static const std::string regKeyWord = "reg";
	
	forEachChildContext(
			_context
		,	[ & ]( antlr4::tree::ParseTree & _tree )
			{
				if( _tree.getText() == regKeyWord )
					m_isReg = true;

				_tree.accept( this );
			}
	);

	if( !m_type )
		initType();
}

/***************************************************************************/

VlogDM::DimensionPtr 
NetExtractor::getDimension()
{
	const int size = m_dimensions.size();
	if( size == 0 )
		return VlogDM::DimensionPtr();

	//if( m_dimensions.size() == 1 )
		return std::move( m_dimensions.front() );
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitNet_type( Verilog2001Parser::Net_typeContext *ctx )
{
	m_netType = VlogDM::NetKind::fromString( ctx->getText().c_str() );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitRange( Verilog2001Parser::RangeContext *ctx )
{
	using namespace VlogDM;

	VlogDM::Location const location = createLocation( *ctx );

	initDimension( 
			NetItem( ctx->children[ 1 ]->getText(), location ) 
		,	NetItem( ctx->children[ 3 ]->getText(), location )
		,	std::bind( 
					&Writable::ItemsFactory::newPackedDimension
				,	std::ref( getVlogDataModel().getItemsFactory() )
				,	std::placeholders::_1
				,	std::placeholders::_2 
			)
	);

	if( !m_type )
		initType();

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitDimension( Verilog2001Parser::DimensionContext *ctx )
{
	using namespace VlogDM;

	VlogDM::Location const location = createLocation( *ctx );

	initDimension( 
			NetItem( ctx->children[ 1 ]->getText(), location ) 
		,	NetItem( ctx->children[ 3 ]->getText(), location )
		,	std::bind( 
					&Writable::ItemsFactory::newUnackedDimension
				,	std::ref( getVlogDataModel().getItemsFactory() )
				,	std::placeholders::_1
				,	std::placeholders::_2 
			)
	);

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitList_of_port_identifiers(
	Verilog2001Parser::List_of_port_identifiersContext *ctx
)
{
	return visitListOfIds( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
NetExtractor::visitList_of_net_identifiers(
		Verilog2001Parser::List_of_net_identifiersContext *ctx
) 
{
	return visitListOfIds( *ctx );
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitPort_identifier( Verilog2001Parser::Port_identifierContext *ctx )
{
	return extractId( *ctx );
}

/***************************************************************************/

antlrcpp::Any 
NetExtractor::visitNet_identifier(
		Verilog2001Parser::Net_identifierContext *ctx
	)
{
	return extractId( *ctx );
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitVariable_identifier(
	Verilog2001Parser::Variable_identifierContext *ctx
)
{
	return extractId( *ctx );
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitListOfIds( antlr4::ParserRuleContext & _context )
{
	acceptEachChildContext( _context );

	return antlrcpp::Any();
}

/***************************************************************************/

antlrcpp::Any 
NetExtractor::extractId( antlr4::ParserRuleContext & _context )
{
	m_netIds.emplace_back( _context.getText(), createLocation( _context ) );

	return antlrcpp::Any();
}

/***************************************************************************/

void 
NetExtractor::initType()
{
	using namespace VlogDM;

	IAccessor & vlogDm = getVlogDataModel();

	Writable::TypeFactory const & typeFactory = vlogDm.getTypeFactory();

	DimensionPtr typeDimension 
		=	m_dimensions.empty() 
			?	DimensionPtr() 
			:	std::move( m_dimensions.front() );  

	if( m_isReg )
	{
		m_type.reset(
			typeFactory.newVariableType( 
					VariableKind::Kind::reg
				,	std::move( typeDimension ) 
			).release()
		);
	}
	else
	{
		m_type.reset( 
			typeFactory.newNetType( 
					m_netType
				,	std::move( typeDimension ) 
			).release() 
		);
	}

	m_dimensions.clear();
}

/***************************************************************************/

void 
NetExtractor::initDimension( 
		NetExtractor::NetItem const & _leftBound
	,	NetExtractor::NetItem const & _rightBound
	,	RangeCreator _creator 
	)
{
	using namespace VlogDM;

	IAccessor & vlogDm = getVlogDataModel();

	Writable::ExpressionFactory const& expressionFactory
		=	vlogDm.getExpressionFactory();

	Writable::ItemsFactory const& itemsFactory
		=	vlogDm.getItemsFactory();

	auto rangeBoundCreator 
		=	[ & ]( NetExtractor::NetItem const& _item )
			{
				return
					std::move(
						expressionFactory.newPrimaryLiteral(
								_item.second
							,	_item.first
						)
					);
			};

	m_dimensions.emplace_back( 
		_creator( 
				_leftBound.second
			,	itemsFactory.newPartSelectRange(
						_leftBound.second
					,	rangeBoundCreator( _leftBound )
					,	rangeBoundCreator( _rightBound )
				)
		).release() 
	);
}

/***************************************************************************/

}
}