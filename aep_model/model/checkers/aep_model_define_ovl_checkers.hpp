#ifndef __AEP_MODEL_DEFINE_OVL_CHECKERS_HPP__
#define __AEP_MODEL_DEFINE_OVL_CHECKERS_HPP__

/***************************************************************************/

#include "aep_model\model\parameters\aep_model_base_checker_parameter_impl.hpp"
#include "aep_model\model\parameters\aep_model_ovl_enum_checker_parameter_impl.hpp"
#include "aep_model\model\checkers\aep_model_ovl_checker_port_impl.hpp"

#include "aep_model\model\checkers\aep_model_ovl_checker_base_impl.hpp"
#include "aep_model\model\aep_model_utils.hpp"

#include <boost\preprocessor\seq\for_each.hpp>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

#define AEP_ADD_GENERIC(_IDX, _PREFIX, _PARAM_TYPE) 						\
		addParameter(														\
			OvlCheckerGenericParameter::Ptr(								\
				new BOOST_PP_CAT( _PARAM_TYPE, ParameterImpl )()			\
			)																\
		);

/***************************************************************************/

#define AEP_ADD_PORT(_IDX, _PREFIX, _PORT) 									\
		addPort(															\
			OvlCheckerPort::Ptr(											\
				new OvlCheckerPortImpl( OvlCheckerPortKind::Kind::_PORT )	\
			)																\
		);	

/***************************************************************************/

#define AEP_DEFINE_OVL_CHECKER(CHECKER_NAME, SPECIFIC_GENERICS, SPECIFIC_PORTS)		 	\
	class Ovl##CHECKER_NAME##Checker													\
		:	public OvlCheckerImpl														\
	{																					\
		public:																			\
																						\
			Ovl##CHECKER_NAME##Checker(													\
					std::string const & _instanceName									\
				,	std::string const & _fileName										\
				,	int _suspectCodeLine												\
			)																			\
				:	OvlCheckerImpl( 													\
							OvlCheckerIds::Kind::Ovl##CHECKER_NAME						\
						,	_instanceName												\
						,	_fileName													\
						,	_suspectCodeLine											\
					)																	\
			{																			\
				BOOST_PP_SEQ_FOR_EACH(													\
						AEP_ADD_GENERIC													\
					,	c_																\
					,	COMMON_GENERICS													\
				);																		\
																						\
				BOOST_PP_SEQ_FOR_EACH(													\
						AEP_ADD_GENERIC													\
					,	s_																\
					,	SPECIFIC_GENERICS												\
				);																		\
																						\
				BOOST_PP_SEQ_FOR_EACH(													\
						AEP_ADD_PORT													\
					,	c_																\
					,	COMMON_PORTS													\
				);																		\
																						\
				BOOST_PP_SEQ_FOR_EACH(													\
						AEP_ADD_PORT													\
					,	s_																\
					,	SPECIFIC_PORTS													\
				);																		\
			}																			\
																						\
	};

/***************************************************************************/

#define OVL_ALWAYS_PORTS 		\
	( TestExpression )		

AEP_DEFINE_OVL_CHECKER( Always, BOOST_PP_SEQ_NIL, OVL_ALWAYS_PORTS )

/***************************************************************************/

#define OVL_ONE_HOT_PORTS 		\
	( TestExpression )		

#define OVL_ONE_HOT_GENERICS	\
	( Width )		

AEP_DEFINE_OVL_CHECKER( OneHot, OVL_ONE_HOT_GENERICS, OVL_ALWAYS_PORTS )

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_DEFINE_OVL_CHECKERS_HPP__
