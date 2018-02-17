#ifndef __VLOG_DM_IACCESSOR_HPP__
#define __VLOG_DM_IACCESSOR_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <boost\noncopyable.hpp>

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
	
	virtual void regenerateProcess( 
			std::ostream & _stream
		,	Process const & _process 
	) const = 0;

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
