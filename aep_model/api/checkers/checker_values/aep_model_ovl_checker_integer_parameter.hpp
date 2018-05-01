#ifndef __AEP_MODEL_OVL_CHECKER_INTEGER_PARAMETER_HPP__
#define __AEP_MODEL_OVL_CHECKER_INTEGER_PARAMETER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_generic_parameter.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlIntegerParameter
	:	public OvlCheckerGenericParameter
{

/***************************************************************************/

	virtual int getValue() const = 0;
	
	virtual void setValue( int _value ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct OVlCheckerIntegerParameterDefaults
{
	static const int MinCycles = 1;
	static const int MaxCycles = 1;
	static const int MinAcknowledgeCycles = 0;
	static const int MaxAcknowledgeCycles = 0;
	static const int MaxAcknowledgeLength = 0;
	static const int RequestDrop = 0;
	static const int DeassertionCount = 0;
	static const int Width = 1;
	static const int Value = 1;
};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_INTEGER_PARAMETER_HPP__
