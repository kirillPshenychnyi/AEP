#ifndef __AEP_FULL_CASE_SYN_DIRECTIVE_CHECKER_HPP__
#define __AEP_FULL_CASE_SYN_DIRECTIVE_CHECKER_HPP__

/***************************************************************************/

#include "aep\checkers\aep_base_case_syn_directive_checker.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

class FullCaseSynDirectiveChecker
	:	public BaseCaseSynDirectiveChecker
{

/***************************************************************************/

public:

/***************************************************************************/

	FullCaseSynDirectiveChecker( IAccessor & _aep );

/***************************************************************************/

	void onCaseStatement( VlogDM::CaseStatement const & _case );

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_FULL_CASE_SYN_DIRECTIVE_CHECKER_HPP__
