#ifndef __VLOG_DM_ACCESSOR_IMPL_HPP__
#define __VLOG_DM_ACCESSOR_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_design_unit.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declaration_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_design_unit_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_type_factory.hpp"

#include "common_tools\base_plugin.hpp"
#include "common_tools\collections\tools_collection_utils.hpp"

#include <boost\functional\hash\hash.hpp>

#include <boost\unordered_set.hpp>

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

class Accessor
	:	public Tools::BasePlugin< IAccessor, Accessor >
{

/***************************************************************************/

	typedef
		Tools::Collections::NamedHasher< DesignUnit::Ptr >
		DesignUnitHasher;

	typedef
		Tools::Collections::NamedComparator< DesignUnit::Ptr >
		DesignUnitComparator;

	typedef
		boost::unordered_set< std::unique_ptr< DesignUnit >, DesignUnitHasher, DesignUnitComparator >
		UnitsSet;

/***************************************************************************/

	friend struct Tools::BasePlugin< IAccessor, Accessor >;

/***************************************************************************/

	Accessor() = default;

/***************************************************************************/

public:

/***************************************************************************/

	void addUnit( std::unique_ptr< DesignUnit > _unit ) override;

	boost::optional< DesignUnit const & > findUnit( 
			std::string const& _unitName 
	) const override;

	void reset() override;

/***************************************************************************/

	Writable::DesignUnitFactory const& getDesignUnitFactory() override;

	Writable::DeclarationFactory const& getDeclarationFactory() override;

	Writable::DeclaredFactory const& getDeclaredFactory() override;

	Writable::ItemsFactory const& getItemsFactory() override;

	Writable::ExpressionFactory const& getExpressionFactory() override;

	Writable::TypeFactory const& getTypeFactory() override;

/***************************************************************************/

private:

/***************************************************************************/

	template< typename _TFactory > 
	std::unique_ptr< _TFactory > getFactory() const;

/***************************************************************************/

	UnitsSet m_unitsSet;

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

#endif // !__VLOG_DM_ACCESSOR_IMPL_HPP__

