#ifndef __VLOG_DM_CASE_KIND_HPP__
#define __VLOG_DM_CASE_KIND_HPP__

/***************************************************************************/

#include "common_tools\utils\convertors.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct CaseKind
{

/***************************************************************************/

	enum class Kind
	{	
			Case
		,	CaseX
		,	CaseZ

		,	First = Case
		,	Last = CaseZ
	};

/***************************************************************************/

	static Kind fromString( const char * const _value )
	{
		return Tools::Convertors::toEnumFromString< CaseKind >( _value );
	}

	static const char * const toString( Kind _type )
	{
		switch( _type )
		{
			case Kind::Case:
				return "case";

			case Kind::CaseZ:
				return "casez";
			
			case Kind::CaseX:
				return "casex";

			default:
				return "";
		}
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_KIND_HPP__
