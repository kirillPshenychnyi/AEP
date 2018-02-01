#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_base_net_importer.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_net_extractor.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_variable_type.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_declared.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declaration.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_type_factory.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

template< typename _Declaration >
BaseNetImporter< _Declaration >::BaseNetImporter( 
		VlogDM::IAccessor & _accessor
	,	VlogDM::Writable::DesignUnit & _targetUnit 
	)
	:	BaseImporter( _accessor )
	,	m_targetUnit( _targetUnit )
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
	
	_Declaration & lastDeclaration 
		= *m_extractedDeclarations.back();
	
	Writable::DeclaredFactory const& declaredFactory 
		=	getVlogDataModel().getDeclaredFactory();

	for( auto const& port : extractor.m_netIds )
		lastDeclaration.addDeclared( 
			_creator( 
					lastDeclaration
				,	createType( extractor )
				,	createDimension( extractor )
				,	port
			)
		);
}

/***************************************************************************/

template< typename _Declaration >
void 
BaseNetImporter< _Declaration >::addDeclarations()
{
	for( auto & value : m_extractedDeclarations )
		m_targetUnit.addDeclaration( std::move( value ) );
}

/***************************************************************************/

template< typename _Declaration >
VlogDM::TypePtr 
BaseNetImporter< _Declaration >::createType(
		NetExtractor const& _extractor
)
{
	using namespace VlogDM;

	IAccessor & vlogDm = getVlogDataModel();

	Writable::TypeFactory const & typeFactory = vlogDm.getTypeFactory();
	 
	if( _extractor.m_isReg )
		return typeFactory.newVariableType(
						VariableKind::Kind::reg
					,	std::move( createDimension( _extractor ) )
				);
		
	return typeFactory.newNetType( 
					_extractor.m_netType
				,	std::move( createDimension( _extractor ) 
			)
	);
}

/***************************************************************************/

template< typename _Declaration >
VlogDM::DimensionPtr 
BaseNetImporter< _Declaration >::createDimension(
		NetExtractor const& _extractor
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

	if(
			_extractor.m_rightBound.is_initialized()
		&&	_extractor.m_leftBound.is_initialized()
	)
	{
		std::unique_ptr< Range > range
			=	itemsFactory.newPartSelectRange(
						_extractor.m_leftBound->second
					,	rangeBoundCreator( *_extractor.m_leftBound )
					,	rangeBoundCreator( *_extractor.m_rightBound )
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

template class BaseNetImporter< VlogDM::Writable::PortDeclaration >;

/***************************************************************************/

}
}