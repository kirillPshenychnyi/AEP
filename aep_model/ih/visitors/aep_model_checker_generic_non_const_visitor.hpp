#ifndef __AEP_MODEL_OVL_CHECKER_GENERIC_NON_VISITOR_HPP__
#define __AEP_MODEL_OVL_CHECKER_GENERIC_NON_VISITOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "aep_model\api\aep_model_fwd.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlCheckerGenericParameterNonConstVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( OvlIntegerParameter & _int ) = 0;

	virtual void visit( OvlStringParameter & _str ) = 0;

	virtual void visit( OvlSeverityLevelParameter & _severity ) = 0;

	virtual void visit( OvlClockEdgeParameter & _clkEdge ) = 0;

	virtual void visit( OvlResetPolarityParameter & _resetPolarity ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct OvlCheckerGenericParameterDefaultNonVisitor
	:	public OvlCheckerGenericParameterNonConstVisitor
{

/***************************************************************************/

	void visit( OvlIntegerParameter & _int ) override {}

	void visit( OvlStringParameter & _str ) override {}

	void visit( OvlSeverityLevelParameter & _severity ) override {}

	void visit( OvlClockEdgeParameter & _clkEdge ) override {}

	void visit( OvlResetPolarityParameter & _resetPolarity ) override {}

/***************************************************************************/

};

/***************************************************************************/

}
 
/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_GENERIC_NON_VISITOR_HPP__
