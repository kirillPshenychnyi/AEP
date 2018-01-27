#ifndef __VLOG_DM_VARIABLE_KIND_HPP__
#define __VLOG_DM_VARIABLE_KIND_HPP__

/***************************************************************************/

#include "common_tools\utils\convertors.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct VariableKind
{

/***************************************************************************/

	enum class Kind
	{
			reg
		,	time
		,	integer
		,	real
		,	realTime

		,	First = reg
		,	Last = realTime
	};
	
	static Kind fromString( const char * const _value )
	{
		return Tools::Convertors::toEnumFromString< VariableKind >( _value );
	}

	static const char * const toString( Kind _kind )
	{
		switch( _kind )
		{
			case Kind::reg:
				return "reg";
			
			case Kind::time:
				return "time";

			case Kind::integer:
				return "integer";

			case Kind::real:
				return "real";

			case Kind::realTime:
				return "realtime";
		}
	}

/***************************************************************************/

};


/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_VARIABLE_KIND_HPP__
