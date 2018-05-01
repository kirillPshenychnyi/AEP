#ifndef __AEP_MODEL_OVL_CHECKER_IDS_HPP__
#define __AEP_MODEL_OVL_CHECKER_IDS_HPP__

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlCheckerIds
{

/***************************************************************************/

	enum class Kind
	{
			OvlAlways
		,	OvlOneHot
	};

/***************************************************************************/

	static const char * const toString( Kind _enum )
	{
		switch( _enum )
		{
			case Kind::OvlAlways:
				return "ovl_always";
			case Kind::OvlOneHot:
				return "ovl_one_hot";

			default:
				return "";
		}
	}
};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_IDS_HPP__
