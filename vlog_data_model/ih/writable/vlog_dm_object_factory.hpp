#ifndef __VLOG_DM_OBJECT_FACTORY_HPP__
#define __VLOG_DM_OBJECT_FACTORY_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct ObjectFactory
{

/***************************************************************************/

	virtual Writable::DesignUnitFactory const& getDesignUnitFactory() const = 0;

	virtual Writable::DeclarationFactory const& getDeclarationFactory() const = 0;

	virtual Writable::DeclaredFactory const& getDeclaredFactory() const = 0;

	virtual Writable::ItemsFactory const& getItemsFactory() const = 0;

	virtual Writable::ExpressionFactory const& getExpressionFactory() const = 0;

	virtual Writable::TypeFactory const& getTypeFactory() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_OBJECT_FACTORY_HPP__
