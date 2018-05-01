#ifndef __AEP_MODEL_OVL_CHECKER_GENERIC_VISITOR_HPP__
#define __AEP_MODEL_OVL_CHECKER_GENERIC_VISITOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "aep_model\api\aep_model_fwd.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlCheckerGenericParameterVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( OvlIntegerParameter const & _int ) = 0;

	virtual void visit( OvlStringParameter const & _str ) = 0;

	virtual void visit( OvlSeverityLevelParameter const & _severity ) = 0;

	virtual void visit( OvlClockEdgeParameter const & _clkEdge ) = 0;

	virtual void visit( OvlResetPolarityParameter const & _resetPolarity ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct OvlCheckerGenericParameterDefaultVisitor
	:	public OvlCheckerGenericParameterVisitor
{

/***************************************************************************/

	void visit( OvlIntegerParameter const & _int ) override {}

	void visit( OvlStringParameter const & _str ) override {}

	void visit( OvlSeverityLevelParameter const & _severity ) override {}

	void visit( OvlClockEdgeParameter const & _clkEdge ) override {}

	void visit( OvlResetPolarityParameter const & _resetPolarity ) override {}

/***************************************************************************/

};

/***************************************************************************/

}
 
/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_GENERIC_VISITOR_HPP__
