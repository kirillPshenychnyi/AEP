#include "stdafx.h"

#include "sources\model\vlog_dm_accessor.hpp"

#include "sources\model\factory\vlog_dm_design_unit_factory_impl.hpp"
#include "sources\model\factory\vlog_dm_declarations_factory_impl.hpp"
#include "sources\model\factory\vlog_dm_declared_factory_impl.hpp"
#include "sources\model\factory\vlog_dm_items_factory_impl.hpp"

/***************************************************************************/

namespace VlogDM {

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
	return *m_itemsFactory;
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
