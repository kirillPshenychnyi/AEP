#ifndef __AEP_MODEL_BASE_CHECKER_BUILDER_IMPL_HPP__
#define __AEP_MODEL_BASE_CHECKER_BUILDER_IMPL_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_builder.hpp"

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"

#include "aep_model\api\aep_model_ovl_checker_generic_param_cast.hpp"

#include "aep_model\api\checkers\checker_values\aep_model_declare_ovl_enum_checker_parameter.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_ovl_checker_string_parameter.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_ovl_checker_integer_parameter.hpp"

#include "aep_model\model\aep_model_utils.hpp"

#include <vector>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

template < typename _TBase >
class BaseOvlCheckerBuilderImpl
	:	public _TBase
{

/***************************************************************************/

public:

/***************************************************************************/

	BaseOvlCheckerBuilderImpl( std::unique_ptr< OvlChecker > _checker )
		:	m_checker( std::move( _checker ) )
	{
	}

	OvlCheckerPtr releaseChecker() final
	{
		return std::move( m_checker );
	}

	AEP_DEFINE_ENUM_PARAM_SETTER( ResetPolarity )
	AEP_DEFINE_ENUM_PARAM_SETTER( SeverityLevel )
	AEP_DEFINE_ENUM_PARAM_SETTER( ClockEdge )

	void setMessage( std::string const & _value ) final
	{
		setGeneric< OvlStringParameter, std::string const & >( 
				GenericType::Kind::Msg
			,	_value
		);
	}

/***************************************************************************/

	AEP_DEFINE_PORT_SETTER( Clock )
	AEP_DEFINE_PORT_SETTER( Reset )	
	AEP_DEFINE_PORT_SETTER( Enable )
	AEP_DEFINE_PORT_SETTER( Fire )

/***************************************************************************/

	template< typename _TargetGeneric, typename _Value >
	void setGeneric (
			GenericType::Kind _type
		,	_Value _value
	)
	{
		auto paramOpt = m_checker->getParameter( _type );
		
		OvlCheckerGenericParameterCast< _TargetGeneric > caster;
		auto castResult = caster.cast( *paramOpt );
		castResult->setValue( _value );
	}

/***************************************************************************/

protected:

/***************************************************************************/

	std::unique_ptr< OvlChecker > m_checker;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_BASE_CHECKER_BUILDER_IMPL_HPP__
