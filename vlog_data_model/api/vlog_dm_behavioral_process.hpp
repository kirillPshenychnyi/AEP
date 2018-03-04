#ifndef __VLOG_DM_BEHAVIORAL_PROCESS_PROCESS_HPP__
#define __VLOG_DM_BEHAVIORAL_PROCESS_PROCESS_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_process.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Statement;
struct SensitivityList;

/***************************************************************************/

struct BehavioralProcess
	:	public Process
{

/***************************************************************************/

	virtual Statement const & getStatement () const = 0;

	virtual boost::optional< SensitivityList const & > getSensitivityList() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_BEHAVIORAL_PROCESS_PROCESS_HPP__
