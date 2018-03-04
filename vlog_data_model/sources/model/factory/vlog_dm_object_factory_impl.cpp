#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_object_factory_impl.hpp"

#include "vlog_data_model\sources\model\factory\vlog_dm_design_unit_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_declarations_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_declared_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_items_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_expression_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_type_factory_impl.hpp"
#include "vlog_data_model\sources\model\factory\vlog_dm_statement_factory_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

ObjectFactoryImpl::ObjectFactoryImpl()
	:	m_designUnitFactory( new DesignUnitFactoryImpl() )
	,	m_declarationFactory( new DeclarationsFactoryImpl() )
	,	m_declaredFactory( new DeclaredFactoryImpl() )
	,	m_itemsFactory( new ItemsFactoryImpl() )
	,	m_expressionFactory( new ExpressionFactoryImpl() )
	,	m_typeFactory( new TypeFactoryImpl() )
	,	m_statementFactory( new StatementFactoryImpl() )
{
}

/***************************************************************************/

Writable::DesignUnitFactory const&
ObjectFactoryImpl::getDesignUnitFactory() const
{
	return *m_designUnitFactory;
}

/***************************************************************************/

Writable::DeclarationFactory const&
ObjectFactoryImpl::getDeclarationFactory() const
{
	return *m_declarationFactory;
}

/***************************************************************************/

Writable::DeclaredFactory const&
ObjectFactoryImpl::getDeclaredFactory() const
{
	return *m_declaredFactory;
}

/***************************************************************************/

Writable::ItemsFactory const &
ObjectFactoryImpl::getItemsFactory() const
{
	return *m_itemsFactory;
}

/***************************************************************************/

Writable::ExpressionFactory const &
ObjectFactoryImpl::getExpressionFactory() const
{
	return *m_expressionFactory;
}

/***************************************************************************/

Writable::TypeFactory const &
ObjectFactoryImpl::getTypeFactory() const
{
	return *m_typeFactory;
}

/***************************************************************************/

Writable::StatementFactory const &
ObjectFactoryImpl::getStatementFactory() const
{
	return *m_statementFactory;
}

/***************************************************************************/

}