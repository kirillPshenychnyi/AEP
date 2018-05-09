#ifndef __AEP_MODEL_OVL_CHECKER_GENERIC_VISITOR_HPP__
#define __AEP_MODEL_OVL_CHECKER_GENERIC_VISITOR_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_fwd.hpp"
#include "common_tools\utils\declare_visitors.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

DECLARE_VISITORS( 
		OvlCheckerGenericParameter 
	,	OvlIntegerParameter
	,	OvlStringParameter
	,	OvlSeverityLevelParameter
	,	OvlClockEdgeParameter
	,	OvlResetPolarityParameter
)

/***************************************************************************/

}
 
/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_GENERIC_VISITOR_HPP__
