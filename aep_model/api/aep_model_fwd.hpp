#ifndef __AEP_MODEL_FWD_HPP__
#define __AEP_MODEL_FWD_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\checker_values\aep_model_reset_polarity.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_clock_edge.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct IAccessor;

struct OvlChecker;
struct OvlCheckerBuilder;
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

typedef
	std::function< void( AssertionContext& ) >
	AssertionContextCallback;

typedef
	std::function< void( AssertionContext const & ) >
	ConstAssertionContextCallback;

struct AssertionContextSet;

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_FWD_HPP__
