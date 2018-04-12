#include "stdafx.h"

#include "aep\checkers\aep_full_case_syn_directive_checker.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

FullCaseSynDirectiveChecker::FullCaseSynDirectiveChecker( VlogDM::IAccessor const & _vlogDm )
	:	BaseCaseSynDirectiveChecker( _vlogDm )
{
}

/***************************************************************************/

void 
FullCaseSynDirectiveChecker::onCaseStatement( VlogDM::CaseStatement const & _case )
{
	int i = 0;
}

/***************************************************************************/

}