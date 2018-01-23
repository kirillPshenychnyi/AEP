#include "stdafx.h"

#include "sources\model\vlog_dm_accessor.hpp"

#include "sources\model\factory\vlog_dm_design_unit_factory_impl.hpp"
#include "sources\model\factory\vlog_dm_declarations_factory_impl.hpp"
#include "sources\model\factory\vlog_dm_declared_factory_impl.hpp"
#include "sources\model\factory\vlog_dm_items_factory_impl.hpp"
#include "sources\model\factory\vlog_dm_expression_factory_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

void 
Accessor::addUnit( std::unique_ptr< DesignUnit > _unit )
{
	m_unitsSet.emplace( std::unique_ptr< DesignUnit >( _unit.release() ) );
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

void 
Accessor::reset()
{
	m_unitsSet.clear();
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

template< typename _TFactory >
std::unique_ptr< _TFactory > 
Accessor::getFactory() const
{
	return std::make_unique< _TFactory >();
}

/***************************************************************************/

}
