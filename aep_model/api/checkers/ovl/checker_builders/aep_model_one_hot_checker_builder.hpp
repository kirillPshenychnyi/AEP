#ifndef __AEP_MODEL_OVL_ONE_HOT_CHECKER_BUILDER_HPP__
#define __AEP_MODEL_OVL_ONE_HOT_CHECKER_BUILDER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_builder.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlOneHotCheckerBuilder
	:	public OvlCheckerBuilder
{

/***************************************************************************/

	virtual void setTestExpression(
			std::string const & _lhs
		,	std::string const & _rhs
		,	int _width = 1
	) = 0;

	virtual void setWidth( int _width ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_ONE_HOT_CHECKER_BUILDER_HPP__
