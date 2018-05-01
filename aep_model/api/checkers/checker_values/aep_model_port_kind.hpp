#ifndef __AEP_MODEL_CHECKER_PORT_KIND_HPP__
#define __AEP_MODEL_CHECKER_PORT_KIND_HPP__

namespace AepModel {

/***************************************************************************/

struct OvlCheckerPortKind
{

/***************************************************************************/

	enum class Kind
	{
			Fire
		,	Reset
		,	Clock
		,	Test
		,	TestExpression
		,	Enable
		,	Request
		,	Acknowledge
	};

/***************************************************************************/

	static const char * const toString( Kind _enum )
	{
		switch( _enum )
		{
			case Kind::Fire:
				return "fire";
			case Kind::Reset:
				return "reset";
			case Kind::Clock:
				return "clock";
			case Kind::Test:
				return "test";
			case Kind::TestExpression:
				return "test_expr";
			case Kind::Enable:
				return "enable";
			case Kind::Request:
				return "req";
			case Kind::Acknowledge:
				return "ack";
			default:
				return "";
		}
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_CHECKER_PORT_KIND_HPP__
