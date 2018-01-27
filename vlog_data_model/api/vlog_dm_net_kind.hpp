#ifndef __VLOG_DM_NET_KIND_HPP__
#define __VLOG_DM_NET_KIND_HPP__

/***************************************************************************/

#include "common_tools\utils\convertors.hpp"

/***************************************************************************/

namespace VlogDM{

/***************************************************************************/

struct NetKind
{
	enum class Kind
	{
			supply0
		,	supply1
		,	tri
		,	triand
		,	trior
		,	tri0
		,	tri1
		,	wire
		,	wand
		,	wor

		,	First = supply0
		,	Last = wor
	};

	static Kind fromString( const char * const _value )
	{
		return Tools::Convertors::toEnumFromString< NetKind >( _value );
	}

	static const char * const toString( Kind _type )
	{
		switch( _type )
		{
			case Kind::supply0:
				return "supply0";

			case Kind::supply1:
				return "supply1";
			
			case Kind::tri:
				return "tri";
			
			case Kind::triand:
				return "triand";
			
			case Kind::trior:
				return "trior";
			
			case Kind::tri0:
				return "tri0";

			case Kind::tri1:
				return "tri1";

			case Kind::wand:
				return "wand";

			case Kind::wor:
				return "wor";

			case Kind::wire:
				return "wire";

			default:
				return "";
		}
	}

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_NET_KIND_HPP__
