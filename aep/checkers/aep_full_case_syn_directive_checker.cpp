#include "stdafx.h"

#include "aep\api\aep_iaccessor.hpp"
#include "aep_model\api\aep_model_iaccessor.hpp"
#include "aep_model\api\checkers\aep_model_ovl_checkers_factory.hpp"
#include "aep_model\api\checkers\ovl\checker_builders\aep_model_always_checker_builder.hpp"

#include "aep\checkers\aep_full_case_syn_directive_checker.hpp"

#include "vlog_data_model\api\vlog_dm_case_statement.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

FullCaseSynDirectiveChecker::FullCaseSynDirectiveChecker( IAccessor & _aep )
	:	BaseCaseSynDirectiveChecker( _aep )
{
}

/***************************************************************************/

void 
FullCaseSynDirectiveChecker::onCaseStatement( VlogDM::CaseStatement const & _case )
{
	using namespace AepModel;

	int i = 0;

	std::unique_ptr< OvlAlwaysCheckerBuilder > checker 
		=	m_accessor.getAepModel().getCheckersFactory().newOvlAlwaysChecker(
				"check_full_case_1"
			,	_case.getLocation().m_file
			,	_case.getLocation().m_beginLine
		);
}

/***************************************************************************/

}