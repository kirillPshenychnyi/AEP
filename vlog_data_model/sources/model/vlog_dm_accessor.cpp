#include "stdafx.h"

#include "vlog_data_model\sources\model\vlog_dm_accessor.hpp"

#include "vlog_data_model\api\vlog_dm_process.hpp"

#include "vlog_data_model\sources\model\factory\vlog_dm_design_unit_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_declarations_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_declared_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_items_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_expression_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_type_factory_impl.hpp"

#include "vlog_data_model\sources\regenerators\vlog_dm_process_regenerator.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

Accessor::Accessor()
	:	m_currentImportedUnit( nullptr )
{
}

/***************************************************************************/

void
Accessor::addUnit( Writable::DesignUnitPtr _unit )
{	
	m_currentImportedUnit = _unit.get();
	m_unitsSet.emplace( std::move( _unit ) );
}

/***************************************************************************/

boost::optional< DesignUnit const& >
Accessor::findUnit( std::string const & _unitName ) const
{
	auto findIt = m_unitsSet.find( _unitName, DesignUnitHasher(), DesignUnitComparator() );

	return 
		findIt == m_unitsSet.end()
	?	boost::optional< DesignUnit const& >()
	:	**findIt;
}

/***************************************************************************/

Writable::DesignUnit &
Accessor::getCurrentImportedUnit()
{
	assert( m_currentImportedUnit );

	return *m_currentImportedUnit;
}

/***************************************************************************/

void 
Accessor::reset()
{
	m_unitsSet.clear();
	m_currentImportedUnit = nullptr;
}

/***************************************************************************/

void 
Accessor::regenerateProcess( std::ostream & _stream, Process const & _process ) const
{
	Regenerators::ProcessRegenerator regenerator( _stream );

	_process.accept( regenerator );
}

/***************************************************************************/

Writable::DesignUnitFactory const&
Accessor::getDesignUnitFactory()
{
	if( !m_designUnitFactory )
		m_designUnitFactory.reset( getFactory< DesignUnitFactoryImpl >().release() );

	return *m_designUnitFactory;
}

/***************************************************************************/

Writable::DeclarationFactory const&
Accessor::getDeclarationFactory()
{
	if( !m_declarationFactory )
		m_declarationFactory.reset( getFactory< DeclarationsFactoryImpl >().release() );

	return *m_declarationFactory;
}

/***************************************************************************/

Writable::DeclaredFactory const&
Accessor::getDeclaredFactory()
{
	if( !m_declaredFactory )
		m_declaredFactory.reset( getFactory< DeclaredFactoryImpl >().release() );

	return *m_declaredFactory;
}

/***************************************************************************/

Writable::ItemsFactory const &
Accessor::getItemsFactory()
{
	if( !m_itemsFactory )
		m_itemsFactory.reset( getFactory< ItemsFactoryImpl >().release() );

	return *m_itemsFactory;
}

/***************************************************************************/

Writable::ExpressionFactory const & 
Accessor::getExpressionFactory()
{
	if( !m_expressionFactory )
		m_expressionFactory.reset( getFactory< ExpressionFactoryImpl >().release() );

	return *m_expressionFactory;
}

/***************************************************************************/

Writable::TypeFactory const &
Accessor::getTypeFactory()
{
	if( !m_typeFactory )
		m_typeFactory.reset( getFactory< TypeFactoryImpl >().release() );

	return *m_typeFactory;
}

/***************************************************************************/

template< typename _TFactory >
std::unique_ptr< _TFactory > 
Accessor::getFactory() const
{
	return std::make_unique< _TFactory >();
}

/***************************************************************************/

}
