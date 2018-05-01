#ifndef __VLOG_DM_DIMENSION_HPP__
#define __VLOG_DM_DIMENSION_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_located.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct DimensionVisitor;
	struct Range;

/***************************************************************************/

struct Dimension
	:	public Located
{
		
/***************************************************************************/

	virtual void accept( DimensionVisitor & _visitor ) const = 0;

	virtual Range const & getRange() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // __VLOG_DM_DIMENSION_HPP__