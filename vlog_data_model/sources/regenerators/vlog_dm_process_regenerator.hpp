#ifndef __VLOG_DM_PROCESS_REGENERATOR_HPP__
#define __VLOG_DM_PROCESS_REGENERATOR_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\regenerators\vlog_dm_base_regenerator.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_process_visitor.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators {

/***************************************************************************/

class ProcessRegenerator
	:	public BaseRegenerator
	,	public ProcessVisitor
{

/***************************************************************************/

public:

/***************************************************************************/

	ProcessRegenerator( std::ostream & _targetStream );

/***************************************************************************/

private:

/***************************************************************************/

	void visit( VlogDM::ContinuousAssignment const & _assing ) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_PROCESS_REGENERATOR_HPP__
