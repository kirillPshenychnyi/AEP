#include "stdafx.h"

#include "aep\api\aep_iaccessor.hpp"

#include "aep_model\api\aep_model_iaccessor.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"
#include "aep_model\api\checkers\aep_model_ovl_checkers_factory.hpp"
#include "aep_model\api\checkers\ovl\checker_builders\aep_model_always_checker_builder.hpp"
#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"

#include "aep\checkers\aep_full_case_syn_directive_checker.hpp"
#include "aep\checkers\resources\aep_checker_resources.hpp"

#include "vlog_data_model\api\vlog_dm_case_statement.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "common_tools\utils\string_utils.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

FullCaseSynDirectiveChecker::FullCaseSynDirectiveChecker( IAccessor & _aep )
	:	BaseCaseSynDirectiveChecker( _aep )
{
}

/***************************************************************************/

std::string 
FullCaseSynDirectiveChecker::getSelWireName() const
{
	return Resources::FullCaseSynDirecriveChecker::CaseSelWire;
}

/***************************************************************************/

std::string 
FullCaseSynDirectiveChecker::getSeparator() const
{
	return Resources::FullCaseSynDirecriveChecker::OrItem;
}

/***************************************************************************/

std::string 
FullCaseSynDirectiveChecker::getCheckTerm() const
{
	return Resources::FullCaseSynDirecriveChecker::CheckTerm;
}

/***************************************************************************/

std::unique_ptr< AepModel::OvlChecker > 
FullCaseSynDirectiveChecker::getOvlChecker( 
		VlogDM::CaseStatement const & _case
	,	std::string const & _caseItems
)
{
	using namespace AepModel;
	using namespace Aep::Resources::FullCaseSynDirecriveChecker;

	static const int checkWireWidth = 1;

	AepModel::IAccessor const & aepAccessor = m_accessor.getAepModel();

	std::unique_ptr< OvlAlwaysCheckerBuilder > checker 
		=	aepAccessor.getCheckersFactory().newOvlAlwaysChecker(
					Tools::fillTemplate( CheckerInstanceName, m_currentSuspectNumber )
				,	_case.getLocation().m_file
				,	_case.getLocation().m_beginLine
			);

	checker->setTestExpression(
			Tools::fillTemplate( CheckExpressionWire, m_currentSuspectNumber )
		,	Tools::fillTemplate( CheckExpression, _caseItems )
		,	checkWireWidth
	);	
	checker->setFire( Tools::fillTemplate( FireWire, m_currentSuspectNumber ) );
	checker->setMessage( Message );
	setControls( *checker );

	return std::move( checker->releaseChecker() );
}

/***************************************************************************/

bool 
FullCaseSynDirectiveChecker::isCheckableCase( 
	VlogDM::CaseStatement const & _case 
) const
{
	return 
		_case.isFullCase() 
	&&	!_case.isParallelCase()
	&&	_case.getDefaultCaseItem() == boost::none;
}

/***************************************************************************/

}