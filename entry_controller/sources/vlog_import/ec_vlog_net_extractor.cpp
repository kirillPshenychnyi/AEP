#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_net_extractor.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_multidimensional_range.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_variable_type.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_type_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"

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

	pushDimension();
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitNet_type( Verilog2001Parser::Net_typeContext *ctx )
{
	m_netType = VlogDM::NetKind::fromString( ctx->getText().c_str() );

	RETURN_ANY
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
	);

	initType();

	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitDimension( Verilog2001Parser::DimensionContext *ctx )
{
	using namespace VlogDM;

	VlogDM::Location const location = createLocation( *ctx );

	m_ranges.emplace_back(
			NetItem( ctx->children[ 1 ]->getText(), location ) 
		,	NetItem( ctx->children[ 3 ]->getText(), location )
	);
	
	RETURN_ANY
}

/***************************************************************************/

antlrcpp::Any
NetExtractor::visitPort_identifier( 
		Verilog2001Parser::Port_identifierContext *ctx 
	)
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
NetExtractor::extractId( antlr4::ParserRuleContext & _context )
{
	if( !m_netIds.empty() )
		pushDimension();

	m_netIds.emplace_back( _context.getText(), createLocation( _context ) );
	
	RETURN_ANY
}

/***************************************************************************/

void 
NetExtractor::initType()
{
	using namespace VlogDM;

	IAccessor & vlogDm = getVlogDataModel();

	Writable::TypeFactory const & typeFactory 
		= vlogDm.getObjectFactory().getTypeFactory();

	if( m_isReg )
	{
		m_type.reset(
			typeFactory.newVariableType( 
					VariableKind::Kind::reg
				,	std::move( m_typeDimension ) 
			).release()
		);
	}
	else
	{
		m_type.reset( 
			typeFactory.newNetType( 
					m_netType
				,	std::move( m_typeDimension ) 
			).release() 
		);
	}
}

/***************************************************************************/

VlogDM::RangePtr 
NetExtractor::createRange( Range const & _dimension )
{
	using namespace VlogDM;

	Writable::ObjectFactory const & objectFactory
		= getVlogDataModel().getObjectFactory();

	Writable::ExpressionFactory const& expressionFactory
		=	objectFactory.getExpressionFactory();

	Writable::ItemsFactory const& itemsFactory
		=	objectFactory.getItemsFactory();

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

	return 
		itemsFactory.newPartSelectRange(
				_dimension.first.second
			,	rangeBoundCreator( _dimension.first )
			,	rangeBoundCreator( _dimension.second )
		);
}

/***************************************************************************/

void 
NetExtractor::initDimension( 
		NetExtractor::NetItem const & _leftBound
	,	NetExtractor::NetItem const & _rightBound
	)
{
	using namespace VlogDM;
	
	Writable::ObjectFactory const & objectFactory
		= getVlogDataModel().getObjectFactory();

	m_typeDimension.reset(
		objectFactory.getItemsFactory().newPackedDimension( 
				_leftBound.second
			,	createRange( Range( _leftBound, _rightBound ) )
		).release()
	);
}

/***************************************************************************/

void
NetExtractor::pushDimension()
{
	using namespace VlogDM;

	if( m_ranges.empty() )
	{
		m_dimensions.push_back( VlogDM::DimensionPtr() );
		return;
	}

	Writable::ObjectFactory const & objectFactory
		= getVlogDataModel().getObjectFactory();

	Writable::ItemsFactory const & itemsFactory
		=	objectFactory.getItemsFactory();

	if( m_ranges.size() == 1 )
	{
		m_dimensions.push_back(
			itemsFactory.newUnackedDimension(
					m_ranges.front().first.second
				,	createRange( m_ranges.front() )
			)
		);
	}
	else
	{
		auto multidimensionalRange
			= itemsFactory.newMultidimensionalRange( m_ranges.front().first.second );

		for( Range const & range : m_ranges )
			multidimensionalRange->addRange( createRange( range ) );

		m_dimensions.push_back(
			itemsFactory.newUnackedDimension(
				m_ranges.front().first.second
				, std::move( multidimensionalRange )
			)
		);
	}

	m_ranges.clear();
}

/***************************************************************************/

VlogDM::DimensionPtr 
NetExtractor::getDimension( int _idx )
{
	if( _idx < m_dimensions.size() )
		return std::move( m_dimensions[ _idx ] );

	return VlogDM::DimensionPtr();
}

/***************************************************************************/

}
}