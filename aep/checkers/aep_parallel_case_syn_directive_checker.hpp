#ifndef __AEP_PARALLEL_CASE_SYN_DIRECTIVE_CHECKER_HPP__
#define __AEP_PARALLEL_CASE_SYN_DIRECTIVE_CHECKER_HPP__

/***************************************************************************/

#include "aep\checkers\aep_base_case_syn_directive_checker.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

class ParallelCaseSynDirectiveChecker
	:	public BaseCaseSynDirectiveChecker
{

/***************************************************************************/

public:

/***************************************************************************/

	ParallelCaseSynDirectiveChecker( IAccessor & _aep );

/***************************************************************************/

private:

/***************************************************************************/

	bool isCheckableCase( VlogDM::CaseStatement const& _case ) const final;

	std::string getSelWireName() const final;

	std::string getSeparator() const final;

	std::string getCheckTerm() const final;

	std::unique_ptr< AepModel::OvlChecker > getOvlChecker(
			VlogDM::CaseStatement const & _case
		,	std::string const & _caseItems
	) final;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_PARALLEL_CASE_SYN_DIRECTIVE_CHECKER_HPP__