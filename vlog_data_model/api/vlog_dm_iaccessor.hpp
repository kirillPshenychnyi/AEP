#ifndef __VLOG_DM_IACCESSOR_HPP__
#define __VLOG_DM_IACCESSOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM
{
	namespace Writable
	{
		struct DeclarationFactory;
		struct DesignUnitFactory;
		struct DeclaredFactory;
		struct ItemsFactory;
		struct ExpressionFactory;
		struct TypeFactory;
	}

	struct DesignUnit;
}

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/
	
struct IAccessor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual boost::optional< DesignUnit const & > findUnit(
			std::string const& _unitName
	) const = 0;

	virtual void addUnit( std::unique_ptr< DesignUnit > _unit ) = 0;

	virtual void reset() = 0;

/***************************************************************************/

	virtual Writable::DesignUnitFactory const& getDesignUnitFactory() = 0;

	virtual Writable::DeclarationFactory const& getDeclarationFactory() = 0;

	virtual Writable::DeclaredFactory const& getDeclaredFactory() = 0;

	virtual Writable::ItemsFactory const& getItemsFactory() = 0;

	virtual Writable::ExpressionFactory const& getExpressionFactory() = 0;

	virtual Writable::TypeFactory const& getTypeFactory() = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_IACCESSOR_HPP__
