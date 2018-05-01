#ifndef __AEP_MODEL_RESET_POLARITY_HPP__
#define __AEP_MODEL_RESET_POLARITY_HPP__

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct ResetPolarity
{

/***************************************************************************/

	enum class Kind
	{
			OVL_ACTIVE_LOW
		,	OVL_ACTIVE_HIGH

		,	Default = OVL_ACTIVE_LOW
	};

/***************************************************************************/

	static const char * const toString( Kind _enum )
	{
		switch ( _enum )
		{
			case Kind::OVL_ACTIVE_LOW:
				return "`OVL_ACTIVE_LOW";
			case Kind::OVL_ACTIVE_HIGH:
				return "`OVL_ACTIVE_HIGH";
			default:
				return toString( Kind::Default );
		}
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_RESET_POLARITY_HPP__
