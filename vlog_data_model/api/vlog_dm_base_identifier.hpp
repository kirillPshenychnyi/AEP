#ifndef __VLOG_DM_BASE_IDENTIFIER_HPP__
#define __VLOG_DM_BASE_IDENTIFIER_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_located.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct BaseIdentifier
	:	public Located
{

/***************************************************************************/

	virtual Declared const & getDeclared() const = 0;

	virtual std::string const& getName() const = 0;

	virtual boost::optional< Range const & > getRange() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_BASE_IDENTIFIER_HPP__
