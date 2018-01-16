#ifndef __VLOG_DM_ACCESSOR_IMPL_HPP__
#define __VLOG_DM_ACCESSOR_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_design_unit_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

class Accessor
	:	public IAccessor
{

/***************************************************************************/

public:

/***************************************************************************/

	Writable::DesignUnitFactory const& getDesignUnitFactory() override;

	Writable::DeclarationFactory const& getDeclarationFactory() override;

	Writable::DeclaredFactory const& getDeclaredFactory() override;

	Writable::ItemsFactory const& getItemsFactory() override;

/***************************************************************************/

private:

/***************************************************************************/

	template< typename _TFactory > 
	std::unique_ptr< _TFactory > getFactory() const;

/***************************************************************************/

	std::unique_ptr< Writable::DesignUnitFactory > m_designUnitFactory;

	std::unique_ptr< Writable::DeclarationFactory > m_declarationFactory;

	std::unique_ptr< Writable::DeclaredFactory > m_declaredFactory;

	std::unique_ptr< Writable::ItemsFactory > m_itemsFactory;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_ACCESSOR_IMPL_HPP__

