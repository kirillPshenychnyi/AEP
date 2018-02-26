#include "stdafx.h"

#include "vlog_data_model\sources\regenerators\vlog_dm_process_regenerator.hpp"
#include "vlog_data_model\sources\regenerators\vlog_dm_expression_regenerator.hpp"

#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators{ 

/***************************************************************************/

ProcessRegenerator::ProcessRegenerator( std::ostream & _targetStream )
	:	BaseRegenerator( _targetStream )
{
}

/***************************************************************************/

void 
ProcessRegenerator::visit( VlogDM::ContinuousAssignment const & _assing )
{
	m_targetStream << "assign ";

	ExpressionRegenerator expressionRegenerator( m_targetStream );

	_assing.getAssignment().accept( expressionRegenerator );

	m_targetStream << ";";
}

/***************************************************************************/

}
}