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

	BaseCaseSynDirectiveChecker( IAccessor & _accessor );

	void analyze() final;

/***************************************************************************/

private:

/***************************************************************************/

	void onProcess( VlogDM::BehavioralProcess const & _process );

	virtual void onCaseStatement( VlogDM::CaseStatement const & _case ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_BASE_CASE_SYN_DIRECTIVE_CHECKER_HPP__