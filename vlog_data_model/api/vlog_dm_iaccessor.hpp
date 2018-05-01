#ifndef __VLOG_DM_IACCESSOR_HPP__
#define __VLOG_DM_IACCESSOR_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <boost\noncopyable.hpp>

#include <functional>

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/
	
struct IAccessor
	:	public boost::noncopyable
{

/***************************************************************************/

	typedef
		std::function< void( DesignUnit const & ) >
		DesignUnitCallback;

/***************************************************************************/

	virtual boost::optional< DesignUnit const & > findUnit(
		std::string const& _unitName
	) const = 0;

	virtual Writable::DesignUnit & getCurrentImportedUnit() = 0;

	virtual void addUnit( Writable::DesignUnitPtr _unit ) = 0;

	virtual void reset() = 0;
	
	virtual void regenerateProcess( 
			std::ostream & _stream
		,	Process const & _process 
	) const = 0;

	virtual std::string regenerateExpression( Expression const & _process ) const = 0;

	virtual Writable::ObjectFactory const& getObjectFactory() const = 0;

	virtual void forEachDesignUnit( DesignUnitCallback _callBack ) const = 0;

	virtual int calculateBitwidth( Expression const & _expression ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_IACCESSOR_HPP__
