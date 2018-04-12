#ifndef __AEP_MODEL_OVL_ENUM_CHECKER_PARAMETER_HPP__
#define __AEP_MODEL_OVL_ENUM_CHECKER_PARAMETER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\checker_values\aep_model_declare_ovl_enum_checker_parameter.hpp"
#include "aep_model\model\parameters\aep_model_base_checker_parameter_impl.hpp"

#include <boost\preprocessor\seq\for_each.hpp>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

#define AEP_DEFINE_ENUM_PARAMETER( NOT_USED1, NOT_USED2, GENERIC )											\
	class BOOST_PP_CAT( GENERIC, ParameterImpl )															\
		:	public BaseCheckerParameterImpl< BOOST_PP_CAT( Ovl, BOOST_PP_CAT( GENERIC, Parameter ) ), GENERIC::Kind, GENERIC::Kind >	\
	{																										\
																											\
		typedef 																							\
			BaseCheckerParameterImpl< BOOST_PP_CAT( Ovl, BOOST_PP_CAT( GENERIC, Parameter ) ), GENERIC::Kind, GENERIC::Kind >	\
			BaseClass;																						\
																											\
		public:																								\
			BOOST_PP_CAT( GENERIC, ParameterImpl )( )														\
				:	BaseClass( GENERIC::Kind::Default, GenericType::Kind::GENERIC ) {}						\
																											\
		std::string valueToString() const 																	\
		{																									\
			return GENERIC::toString( getValue() );															\
		}																									\
																											\
	};																										\

	
/***************************************************************************/

BOOST_PP_SEQ_FOR_EACH( AEP_DEFINE_ENUM_PARAMETER, _, AEP_OVL_ENUM_CHECKER_PARAMS )

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_ENUM_CHECKER_PARAMETER_HPP__
