#ifndef __VLOG_DM_OPERATOR_HPP__
#define __VLOG_DM_OPERATOR_HPP__

/***************************************************************************/

#include "common_tools\utils\convertors.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Operator
{

/***************************************************************************/

	enum class Kind
	{
			Unknown

		,	Assign
		
		,	Plus
		,	Minus
		,	Mul
		,	Div
		
		,	And
		,	Or
		,	Not
		,	Xor

		,	LogicAnd
		,	LogicOr
		,	LogicXor
		,	LogicNot

		,	First = Assign
		,	Last = LogicNot
	};

/***************************************************************************/

	static Kind fromString( const char * const _value )
	{
		return Tools::Convertors::toEnumFromString< Operator >( _value );
	}

/***************************************************************************/

	static const char * const toString( Kind _operator )
	{
		switch( _operator )
		{
			case Kind::Assign:
				return "=";

			case Kind::Plus:
				return "+";
			case Kind::Minus:
				return "-";
			case Kind::Mul:
				return "*";
			case Kind::Div:
				return "/";

			case Kind::And:
				return "&";
			case Kind::Or:
				return "|";
			case Kind::Not:
				return "~";
			case Kind::Xor:
				return "^";

			case Kind::LogicAnd:
				return "&&";
			case Kind::LogicOr:
				return "||";
			case Kind::LogicXor:
				return "^";
			case Kind::LogicNot:
				return "!";
			
			default:
				return "";
		}
	}

	static bool isUnary( Kind _operator )
	{
		return _operator == Kind::Not || _operator == Kind::LogicNot;
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_OPERATOR_HPP__
