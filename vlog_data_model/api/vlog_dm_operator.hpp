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
		
		,	Plus		// +
		,	Minus		// -
		,	Mul			// *
		,	Div			// /
		
		,	And			// &
		,	Or			// |
		,	Not			// ~
		,	Xor			// ^
			
		,	ReductionAnd	// & 
		,	ReductionNand	// ~&
		,	ReductionOr		// | 
		,	ReductionNor	// ~|
		,	ReductionXor	// ~^ or ^~

		,	LogicAnd	// &&
		,	LogicOr		// ||
		,	LogicNot	// !
	
		,	Less			// <
		,	LessEq			// <=
		,	Greater			// >
		,	GreaterEq		// >=

		,	Equal			// ==
		,	WildcardEqual	// ===

		,	First = Assign
		,	Last = WildcardEqual
	};

/***************************************************************************/

	static Kind fromString( const char * const _value )
	{
		if( !strcmp( _value, "~^" ) || !strcmp( _value, "~^" ) )
			return Kind::ReductionXor;

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
			case Kind::ReductionAnd:
				return "&";
			case Kind::Or:
			case Kind::ReductionOr:
				return "|";
			case Kind::Not:
				return "~";
			case Kind::Xor:
				return "^";

			case Kind::Less:
				return "<";

			case Kind::LessEq:
				return "<=";

			case Kind::Greater:
				return ">";
			
			case Kind::GreaterEq:
				return ">=";

			case Kind::LogicAnd:
				return "&&";
			case Kind::LogicOr:
				return "||";
			case Kind::LogicNot:
				return "!";
			
			case Kind::Equal:
				return "==";

			case Kind::WildcardEqual:
				return "===";

			case Kind::ReductionNand: return "~&";
			case Kind::ReductionNor: return "~|";
			case Kind::ReductionXor: return "~^";

			default:
				return "";
		}
	}

	static bool isUnary( Kind _operator )
	{
		switch( _operator )
		{
			case Kind::Plus:
			case Kind::Minus:
			case Kind::Not:
			case Kind::LogicNot:
			case Kind::ReductionAnd:
			case Kind::ReductionNand:
			case Kind::ReductionOr:
			case Kind::ReductionNor:
			case Kind::ReductionXor:
				return true;
			default: 
				return false;
		}
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_OPERATOR_HPP__
