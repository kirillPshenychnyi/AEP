#ifndef __DECLARE_VISITORS_HPP__
#define __DECLARE_VISITORS_HPP__

/***************************************************************************/

#include "common_tools\utils\default_visitor.hpp"
#include "common_tools\utils\base_visitor.hpp"

/***************************************************************************/

namespace Tools {

/***************************************************************************/

#define DECLARE_VISITORS( NAME, ... )				\
	DECLARE_VISITOR( NAME, __VA_ARGS__ )			\
	DECLARE_DEFAULT_VISITOR( NAME, __VA_ARGS__ )	\

/***************************************************************************/

}

/***************************************************************************/

#endif // !__DECLARE_VISITORS_HPP__
