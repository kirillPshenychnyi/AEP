#ifndef __AEP_MODEL_OVL_CHECKER_GENERIC_VISITOR_HPP__
#define __AEP_MODEL_OVL_CHECKER_GENERIC_VISITOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlCheckerIntegerParameter;
struct OvlCheckerStringParameter;
struct SeverityLevelParameter;
struct ResetPolarityParameter;
struct ClockEdgeParameter;

/***************************************************************************/

struct OvlCheckerGenericVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( OvlCheckerIntegerParameter const & _int ) = 0;

	virtual void visit( OvlCheckerStringParameter const & _str ) = 0;

	virtual void visit( SeverityLevelParameter const & _severity ) = 0;

	virtual void visit( ClockEdgeParameter const & _clkEdge ) = 0;

	virtual void visit( ResetPolarityParameter const & _resetPolarity ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}
 
/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_GENERIC_VISITOR_HPP__
