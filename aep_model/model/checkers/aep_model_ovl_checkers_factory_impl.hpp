#ifndef __AEP_MODEL_OVL_CHECKERS_FACTORY_IMPL_HPP__
#define __AEP_MODEL_OVL_CHECKERS_FACTORY_IMPL_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\aep_model_ovl_checkers_factory.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

class OvlCheckersFactoryImpl
	:	public OvlCheckersFactory
{

/***************************************************************************/

	std::unique_ptr< OvlAlwaysCheckerBuilder > newOvlAlwaysChecker(
			std::string const & _instanceName
		,	std::string const & _fileName
		,	int _suspectLine
	) const final;

	std::unique_ptr< OvlOneHotCheckerBuilder > newOvlOneHotChecker(
				std::string const & _instanceName
			,	std::string const & _fileName
			,	int _suspectLine
	) const final;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKERS_FACTORY_IMPL_HPP__