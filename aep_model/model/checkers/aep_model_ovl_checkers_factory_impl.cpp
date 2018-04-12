
#include "stdafx.h"

#include "aep_model\model\checkers\aep_model_ovl_checkers_factory_impl.hpp"

#include "aep_model\model\checkers\checkers_builders\aep_model_ovl_one_hot_checker_builder.hpp"

#include "aep_model\model\checkers\aep_model_define_ovl_checkers.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

std::unique_ptr< OvlOneHotCheckerBuilder >
OvlCheckersFactoryImpl::newOvlOneHotChecker( 
		std::string const & _instanceName
	,	std::string const & _fileName
	,	int _suspectLine 
)
{
	return 
		std::make_unique< OvlOneHotCheckerBuilderImpl >(
			std::make_unique< OvlOneHotChecker >(
					_instanceName
				,	_fileName
				,	_suspectLine 
			)
		);
}

/***************************************************************************/

}