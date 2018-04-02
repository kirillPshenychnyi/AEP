#ifndef __AEP_MODEL_OVL_CHECKER_HPP__
#define __AEP_MODEL_OVL_CHECKER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_ids.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_port_kind.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_generic_type.hpp"

#include <boost\noncopyable.hpp>

#include <functional>

/***************************************************************************/

namespace AepModel
{

/***************************************************************************/

struct OVlCheckerGenericParameter;
struct OvlCheckerPort;

/***************************************************************************/

struct OvlChecker
	:	public boost::noncopyable
{

/***************************************************************************/

	typedef
		std::function< void( OVlCheckerGenericParameter const& ) >
		GenericParameterCallback;

/***************************************************************************/

	virtual OvlCheckerIds::Kind getId() const = 0;

	virtual void setPort(
			OvlCheckerPortKind::Kind _type
		,	std::string const & _value
	) = 0;

	virtual std::string const & getModuleFileName() const = 0;

	virtual int getSuspectCodeLine() const = 0;

	virtual int getGenericsCount() const = 0;

	virtual int getPortsCount() const = 0;

	virtual int getWiresCount() const = 0;

	virtual std::string const & getInstanceName() const = 0;

	virtual boost::optional< OVlCheckerGenericParameter& >
	getParameter( GenericType::Kind _type ) const = 0;

	virtual boost::optional < OvlCheckerPort & > getPort(
		OvlCheckerPortKind::Kind _type
	) const = 0;

	virtual void setPort(
			OvlCheckerPortKind::Kind _type
		,	std::string const & _value
	) const = 0;

	virtual void foreachGeneric( 
		GenericParameterCallback const & _functor 
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_HPP__
