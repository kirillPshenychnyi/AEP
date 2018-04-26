#ifndef __AEP_MODEL_OVL_CHECKER_BUILDER_HPP__
#define __AEP_MODEL_OVL_CHECKER_BUILDER_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_fwd.hpp"

#include "aep_model\api\checkers\checker_values\aep_model_reset_polarity.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_clock_edge.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_severity_level.hpp"

#include <boost\noncopyable.hpp>

/***************************************************************************/

#define AEP_DECLARE_PORT_SETTER( NAME ) \
	virtual void set##NAME ( std::string const & _value ) = 0;

/***************************************************************************/

#define AEP_DECLARE_GENERIC_SETTER( NAME, TYPE ) \
	virtual void set##NAME ( TYPE _value ) = 0;


/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlCheckerBuilder
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual OvlCheckerPtr releaseChecker() = 0;

	AEP_DECLARE_PORT_SETTER( Clock )
	AEP_DECLARE_PORT_SETTER( Reset )
	AEP_DECLARE_PORT_SETTER( Enable )
	AEP_DECLARE_PORT_SETTER( Fire )

/***************************************************************************/

	AEP_DECLARE_GENERIC_SETTER( SeverityLevel, SeverityLevel::Kind )
	AEP_DECLARE_GENERIC_SETTER( ClockEdge, ClockEdge::Kind )
	AEP_DECLARE_GENERIC_SETTER( ResetPolarity, ResetPolarity::Kind )
	AEP_DECLARE_GENERIC_SETTER( Message, std::string const & )

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_HELPER_HPP__
