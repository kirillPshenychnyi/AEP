#ifndef __VLOG_DM_OBJECT_FACTORY_IMPL_HPP__
#define __VLOG_DM_OBJECT_FACTORY_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_design_unit_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_type_factory.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"

/***************************************************************************/

namespace VlogDM
{ 

/***************************************************************************/

class ObjectFactoryImpl
	:	public Writable::ObjectFactory
{

/***************************************************************************/

public:

/***************************************************************************/

	ObjectFactoryImpl();

/***************************************************************************/

	Writable::DesignUnitFactory const& getDesignUnitFactory() const override;

	Writable::DeclarationFactory const& getDeclarationFactory() const override;

	Writable::DeclaredFactory const& getDeclaredFactory() const override;

	Writable::ItemsFactory const& getItemsFactory() const override;

	Writable::ExpressionFactory const& getExpressionFactory() const override;

	Writable::TypeFactory const& getTypeFactory() const override;


/***************************************************************************/

	std::unique_ptr< Writable::DesignUnitFactory > m_designUnitFactory;

	std::unique_ptr< Writable::DeclarationFactory > m_declarationFactory;

	std::unique_ptr< Writable::DeclaredFactory > m_declaredFactory;

	std::unique_ptr< Writable::ItemsFactory > m_itemsFactory;

	std::unique_ptr< Writable::ExpressionFactory > m_expressionFactory;

	std::unique_ptr< Writable::TypeFactory > m_typeFactory;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_OBJECT_FACTORY_IMPL_HPP__
