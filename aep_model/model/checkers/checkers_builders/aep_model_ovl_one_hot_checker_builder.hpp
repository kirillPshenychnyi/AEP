#ifndef __AEP_MODEL_OVL_ONE_HOT_CHECKER_BUILDER_HPP_IMPL__
#define __AEP_MODEL_OVL_ONE_HOT_CHECKER_BUILDER_HPP_IMPL__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\checker_builders\aep_model_one_hot_checker_builder.hpp"

#include "aep_model\model\checkers\checkers_builders\aep_model_base_checker_builder_impl.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

class OvlOneHotCheckerBuilderImpl
	:	public BaseOvlCheckerBuilderImpl< OvlOneHotCheckerBuilder >
{

/***************************************************************************/

	typedef
		BaseOvlCheckerBuilderImpl< OvlOneHotCheckerBuilder >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	OvlOneHotCheckerBuilderImpl( std::unique_ptr< OvlChecker > _checker )
		:	BaseClass( std::move( _checker ) )
	{
	}

	void setTestExpression(
			std::string const & _lhs
		,	std::string const & _rhs
		,	int _width
	) final
	{
		m_checker->setPortAsWire( 
				OvlCheckerPortKind::Kind::TestExpression
			,	_lhs
			,	_rhs
			,	_width 
		);
	}

/***************************************************************************/

	void setWidth( int _width ) final
	{
		setGeneric< OvlIntegerParameter, int >(
				GenericType::Kind::Width
			,	_width
		);
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_ONE_HOT_CHECKER_BUILDER_HPP_IMPL__
