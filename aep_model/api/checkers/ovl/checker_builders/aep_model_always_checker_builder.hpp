#ifndef __AEP_ALWAYS_CHECKER_BUILDER_HPP__
#define __AEP_ALWAYS_CHECKER_BUILDER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_builder.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlAlwaysCheckerBuilder
	:	public OvlCheckerBuilder
{

/***************************************************************************/

	virtual void setTestExpression(
			std::string const & _lhs
		,	std::string const & _rhs
		,	int _width
	) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_ALWAYS_CHECKER_BUILDER_HPP__
