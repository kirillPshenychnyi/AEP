
#include "stdafx.h"

#include "aep_model\model\checkers\aep_model_ovl_checkers_factory_impl.hpp"

#include "aep_model\model\checkers\checkers_builders\aep_model_ovl_always_checker_builder.hpp"

#include "aep_model\model\checkers\aep_model_define_ovl_checkers.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

std::unique_ptr< OvlAlwaysCheckerBuilder >
OvlCheckersFactoryImpl::newOvlAlwaysChecker( 
		std::string const & _instanceName
	,	std::string const & _fileName
	,	int _suspectLine 
) const
{
	return 
		std::make_unique< OvlAlwaysCheckerBuilderImpl >(
			std::make_unique< OvlAlwaysChecker >(
					_instanceName
				,	_fileName
				,	_suspectLine 
			)
		);
}

/***************************************************************************/

}