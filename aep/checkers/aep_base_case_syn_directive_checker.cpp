#include "stdafx.h"

#include "aep\checkers\aep_base_case_syn_directive_checker.hpp"

#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"
#include "vlog_data_model\api\vlog_dm_case_statement.hpp"

#include "aep\utils\aep_utils_statement_query.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

BaseCaseSynDirectiveChecker::BaseCaseSynDirectiveChecker( 
		IAccessor & _accessor 
)
	:	BaseAepChecker( _accessor )
{
}

/***************************************************************************/

void 
BaseCaseSynDirectiveChecker::analyze()
{
	browseProcesses< VlogDM::BehavioralProcess >(
		std::bind( 
				&BaseCaseSynDirectiveChecker::onProcess
			,	this
			,	std::placeholders::_1 
		)
	);
}

/***************************************************************************/

void
BaseCaseSynDirectiveChecker::onProcess( VlogDM::BehavioralProcess const & _process )
{
	Utils::StatementQuery< VlogDM::CaseStatement > caseStmtQuery(
			_process
		,	std::bind( 
					&BaseCaseSynDirectiveChecker::onCaseStatement
				,	this
				,	std::placeholders::_1 
			)
	);

	caseStmtQuery.query();
}

/***************************************************************************/

}