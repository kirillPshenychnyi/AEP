#ifndef __AEP_MODEL_SEVERITY_LEVEL_HPP__
#define __AEP_MODEL_SEVERITY_LEVEL_HPP__

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct SeverityLevel
{

/***************************************************************************/

	enum class Kind
	{
			OVL_FATAL
		,	OVL_ERROR
		,	OVL_WARNING
		,	OVL_INFO

		,	Default = OVL_ERROR
	};

/***************************************************************************/

	static const char * const toString( Kind _enum )
	{
		switch ( _enum )
		{
			case Kind::OVL_FATAL:
				return "`OVL_FATAL";
			case Kind::OVL_ERROR:
				return "`OVL_ERROR";
			case Kind::OVL_WARNING:
				return "`OVL_WARNING";
			case Kind::OVL_INFO:
				return "`OVL_INFO";
			default:
				return toString( Kind::Default );
		}
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_SEVERITY_LEVEL_HPP__
