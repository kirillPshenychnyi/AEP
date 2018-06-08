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

	virtual std::string getSelWireName() const = 0;

	virtual std::string getSeparator() const = 0;

	virtual std::string getCheckTerm() const = 0;

	virtual std::unique_ptr< AepModel::OvlChecker > getOvlChecker(
				VlogDM::CaseStatement const & _case
			,	std::string const & _caseItems
	) = 0;

	void onProcess( VlogDM::BehavioralProcess const & _process );

	virtual bool isCheckableCase( VlogDM::CaseStatement const& _case ) const = 0;

	void onCaseStatement( VlogDM::CaseStatement const & _case );

	void regenerateExpressionItems(
			std::string const & _caseExpression
		,	std::stringstream & _ostream
		,	VlogDM::CaseItem const & _item
	);

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_BASE_CASE_SYN_DIRECTIVE_CHECKER_HPP__