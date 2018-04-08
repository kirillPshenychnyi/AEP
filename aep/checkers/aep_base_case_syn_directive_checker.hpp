#ifndef __AEP_BASE_CASE_SYN_DIRECTIVE_CHECKER_HPP__
#define __AEP_BASE_CASE_SYN_DIRECTIVE_CHECKER_HPP__

/***************************************************************************/

#include "aep\checkers\aep_base_checker.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

class BaseCaseSynDirectiveChecker
	:	public BaseAepChecker
{

/***************************************************************************/

public:

/***************************************************************************/

	BaseCaseSynDirectiveChecker( VlogDM::IAccessor const & _accessor );

	void analyze() final;

/***************************************************************************/

private:

/***************************************************************************/

	void onProcess( VlogDM::BehavioralProcess const & _process );

	void onCaseStatement( VlogDM::CaseStatement const & _case );

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_BASE_CASE_SYN_DIRECTIVE_CHECKER_HPP__