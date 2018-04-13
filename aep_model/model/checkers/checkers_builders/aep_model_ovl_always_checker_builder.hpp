#ifndef __AEP_MODEL_OVL_ALWAYS_CHECKER_BUILDER_IMPL_HPP__
#define __AEP_MODEL_OVL_ALWAYS_CHECKER_BUILDER_IMPL_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\checker_builders\aep_model_always_checker_builder.hpp"

#include "aep_model\model\checkers\checkers_builders\aep_model_base_checker_builder_impl.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

class OvlAlwaysCheckerBuilderImpl
	:	public BaseOvlCheckerBuilderImpl< OvlAlwaysCheckerBuilder >
{

/***************************************************************************/

	typedef
		BaseOvlCheckerBuilderImpl< OvlAlwaysCheckerBuilder >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	OvlAlwaysCheckerBuilderImpl( std::unique_ptr< OvlChecker > _checker )
		:	BaseClass( std::move( _checker ) )
	{
	}

	void setTestExpression(
			std::string const & _lhs
		,	std::string const & _rhs
		,	int _width
	) final
	{

	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_ALWAYS_CHECKER_BUILDER_IMPL_HPP__
