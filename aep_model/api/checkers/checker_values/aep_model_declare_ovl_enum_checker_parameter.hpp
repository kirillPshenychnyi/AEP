#ifndef __AEP_MODEL_DECLARE_OVL_ENUM_CHECKER_PARAMETER_HPP__
#define __AEP_MODEL_DECLARE_OVL_ENUM_CHECKER_PARAMETER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_generic_parameter.hpp"

#include "aep_model\api\checkers\checker_values\aep_model_reset_polarity.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_clock_edge.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_severity_level.hpp"

#include <boost\preprocessor\seq\for_each.hpp>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

#define AEP_DECLARE_ENUM_PARAMETER( NOT_USED1, NOT_USED2, GENERIC )			\
	struct BOOST_PP_CAT( GENERIC, Parameter )								\
		:	public OVlCheckerGenericParameter								\
	{																		\
		virtual GENERIC::Kind getValue() const = 0;							\
																			\
		virtual void setValue( GENERIC::Kind _value ) = 0;					\
	};																		\

/***************************************************************************/

#define	AEP_OVL_ENUM_CHECKER_PARAMS		\
	( ClockEdge )						\
	( ResetPolarity )					\
	( SeverityLevel )

/***************************************************************************/

BOOST_PP_SEQ_FOR_EACH( AEP_DECLARE_ENUM_PARAMETER, _, AEP_OVL_ENUM_CHECKER_PARAMS )

/***************************************************************************/

}

#endif // !__AEP_MODEL_DECLARE_OVL_ENUM_CHECKER_PARAMETER_HPP__
