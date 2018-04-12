#ifndef __AEP_MODEL_CHECKER_INTEGER_PARAMETER_HPP__
#define __AEP_MODEL_CHECKER_INTEGER_PARAMETER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_generic_parameter.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlStringParameter
	:	public OvlCheckerGenericParameter
{

/***************************************************************************/

	virtual std::string const & getValue() const = 0;

	virtual void setValue( std::string const & _value ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__AEP_MODEL_CHECKER_INTEGER_PARAMETER_HPP__
