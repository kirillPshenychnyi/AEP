#ifndef __VLOG_DM_DIMENSIONAL_HPP__
#define __VLOG_DM_DIMENSIONAL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_located.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

	struct Dimension;
	
/***************************************************************************/

struct Dimensional 
	: public boost::noncopyable
{

/***************************************************************************/

	virtual ~Dimensional() = default;

	virtual boost::optional< Dimension const & > getDimension() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_DIMENSIONAL_HPP__
