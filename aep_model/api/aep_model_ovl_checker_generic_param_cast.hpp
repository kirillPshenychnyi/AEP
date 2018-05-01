#ifndef __AEP_MODEL_OVL_CHECKER_GENERIC_PARAM_CAST_HPP__
#define __AEP_MODEL_OVL_CHECKER_GENERIC_PARAM_CAST_HPP__

/***************************************************************************/

#include "aep_model\ih\visitors\aep_model_checker_generic_non_const_visitor.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_generic_parameter.hpp"

#include "common_tools\utils\visitor_cast.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

template< typename _TargetType >
class OvlCheckerGenericParameterCast
	:	public Tools::Cast< 
				_TargetType
			,	OvlCheckerGenericParameter
			,	OvlCheckerGenericParameterDefaultNonVisitor
			,	Tools::NonConstTraits 
		>
{

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_GENERIC_PARAM_CAST_HPP__
