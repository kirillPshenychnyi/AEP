#ifndef __AEP_MODEL_FWD_HPP__
#define __AEP_MODEL_FWD_HPP__

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct IAccessor;

struct OvlChecker;

typedef
	std::unique_ptr< OvlChecker >
	OvlCheckerPtr;

struct OvlIntegerParameter;
struct OvlStringParameter;
struct OvlSeverityLevelParameter;
struct OvlResetPolarityParameter;
struct OvlClockEdgeParameter;

struct OvlCheckersFactory;
struct OvlAlwaysCheckerBuilder;

struct AssertionContext;
typedef
	std::unique_ptr< AssertionContext >
	AssertionContextPtr;

struct AssertionContextSet;

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_FWD_HPP__
