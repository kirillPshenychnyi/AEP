#ifndef __VLOG_DM_NET_TYPE_HPP__
#define __VLOG_DM_NET_TYPE_HPP__

/***************************************************************************/

namespace VlogDM{

/***************************************************************************/

struct NetType
{
	enum class Type
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
		,	reg

		,	First = supply0
		,	Last = reg
	};

	static Type fromString( const char * const _value )
	{
		for( 
			int i = static_cast< int >( Type::First );
			i <= static_cast< int >( Type::Last ); 
			++i 
		)
		{
			Type toCompare = static_cast< Type >( i );

			if( !strcmp( _value, toString( toCompare ) ) )
				return toCompare;
		}

		return Type::First;;
	}

	static const char * const const toString( Type _type )
	{
		switch( _type )
		{
			case Type::supply0:
				return "supply0";

			case Type::supply1:
				return "supply1";
			
			case Type::tri:
				return "tri";
			
			case Type::triand:
				return "triand";
			
			case Type::trior:
				return "trior";
			
			case Type::tri0:
				return "tri0";

			case Type::tri1:
				return "tri1";

			case Type::wand:
				return "wand";

			case Type::wor:
				return "wor";

			case Type::wire:
				return "wire";

			default:
				return "";
		}
	}

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_NET_TYPE_HPP__
