#ifndef __AEP_ONE_HOT_CHECKER_BUILDER_HPP__
#define __AEP_ONE_HOT_CHECKER_BUILDER_HPP__

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
		,	int _width
	) = 0;

	AEP_DECLARE_GENERIC_SETTER( Width, int );

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_ONE_HOT_CHECKER_BUILDER_HPP__
