#ifndef __AEP_MODEL_OVL_CHECKERS_FACTORY_HPP__
#define __AEP_MODEL_OVL_CHECKERS_FACTORY_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_fwd.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlCheckersFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual ~OvlCheckersFactory() = default;

	virtual std::unique_ptr< OvlAlwaysCheckerBuilder > newOvlAlwaysChecker(
				std::string const & _instanceName
			,	std::string const & _fileName
			,	int _suspectLine
	) const = 0;

	virtual std::unique_ptr< OvlOneHotCheckerBuilder > newOvlOneHotChecker(
				std::string const & _instanceName
			,	std::string const & _fileName
			,	int _suspectLine
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKERS_FACTORY_HPP__
