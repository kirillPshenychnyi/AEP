#ifndef __VLOG_DM_DIMENSION_VISITOR_HPP__
#define __VLOG_DM_DIMENSION_VISITOR_HPP__

/***************************************************************************/

#include "common_tools\utils\default_visitor.hpp"
#include "common_tools\utils\base_visitor.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct PackedDimension;
	struct UnpackedDimension;

/***************************************************************************/

DECLARE_VISITOR( Dimension, PackedDimension, UnpackedDimension )

DECLARE_DEFAULT_VISITOR( Dimension, PackedDimension, UnpackedDimension )

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DIMENSION_VISITOR_HPP__
