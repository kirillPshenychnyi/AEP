#ifndef __AEP_FULL_CASE_SYN_DIRECTIVE_CHECKER_HPP__
#define __AEP_FULL_CASE_SYN_DIRECTIVE_CHECKER_HPP__

/***************************************************************************/

#include "aep\sources\checkers\aep_base_case_syn_directive_checker.hpp"

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

private:

/***************************************************************************/

	bool isCheckableCase( VlogDM::CaseStatement const& _case ) const final;

	std::string getSelWireName() const final;

	std::string getSeparator() const final;

	std::string getCheckTerm() const final;

	std::unique_ptr< AepModel::OvlCheckerBuilder > getOvlChecker(
			VlogDM::CaseStatement const & _case
		,	std::string const & _caseItems
		,	std::string const & _caseExpressionWire
	) final;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_FULL_CASE_SYN_DIRECTIVE_CHECKER_HPP__
