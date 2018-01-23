#ifndef __TOOLS_BASE_PLUGIN__
#define __TOOLS_BASE_PLUGIN__

/***************************************************************************/

#include "boost\noncopyable.hpp"

#include <unordered_map>

/***************************************************************************/

namespace Tools {

/***************************************************************************/

template< typename _TBase, typename _TImpl >
struct BasePlugin
	:	public _TBase
{

/***************************************************************************/

	static _TBase& getInstance()
	{
		static std::unique_ptr< _TBase > s_instance;

		if( !s_instance )
			s_instance.reset( new _TImpl() );

		return *s_instance;
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__TOOLS_BASE_PLUGIN__
