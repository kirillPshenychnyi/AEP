#include "stdafx.h"

#include "aep\checkers\aep_parallel_case_syn_directive_checker.hpp"
#include "aep\checkers\resources\aep_checker_resources.hpp"
#include "aep\api\aep_iaccessor.hpp"

#include "aep_model\api\aep_model_iaccessor.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"
#include "aep_model\api\checkers\aep_model_ovl_checkers_factory.hpp"
#include "aep_model\api\checkers\ovl\checker_builders\aep_model_one_hot_checker_builder.hpp"

#include "vlog_data_model\api\vlog_dm_case_statement.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "common_tools\utils\string_utils.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

ParallelCaseSynDirectiveChecker::ParallelCaseSynDirectiveChecker( IAccessor & _aep )
	:	BaseCaseSynDirectiveChecker( _aep )
{
}

/***************************************************************************/

bool 
ParallelCaseSynDirectiveChecker::isCheckableCase( 
	VlogDM::CaseStatement const & _case 
) const
{
	return 
		_case.isParallelCase() 
	&&	!_case.isFullCase()
	&&	_case.getDefaultCaseItem() == boost::none;
}

/***************************************************************************/

std::string 
ParallelCaseSynDirectiveChecker::getSelWireName() const
{
	return Resources::ParallelCaseSynDirecriveChecker::CaseSelWire;
}

/***************************************************************************/

std::string 
ParallelCaseSynDirectiveChecker::getSeparator() const
{
	return Resources::Separators::Coma;
}

/***************************************************************************/

std::string 
ParallelCaseSynDirectiveChecker::getCheckTerm() const
{
	return Resources::ParallelCaseSynDirecriveChecker::CheckTerm;
}

/***************************************************************************/

std::unique_ptr< AepModel::OvlCheckerBuilder > 
ParallelCaseSynDirectiveChecker::getOvlChecker( 
		VlogDM::CaseStatement const & _case
	,	std::string const & _caseItems 
	,	std::string const & _caseExpressionWire
)
{
	using namespace AepModel;
	using namespace Resources::ParallelCaseSynDirecriveChecker;

	AepModel::IAccessor const & aepAccessor = m_accessor.getAepModel();

	std::unique_ptr< OvlOneHotCheckerBuilder > checker 
		=	aepAccessor.getCheckersFactory().newOvlOneHotChecker(
					Tools::fillTemplate( CheckerInstanceName, m_currentSuspectNumber )
				,	_case.getLocation().m_file
				,	_case.getLocation().m_beginLine
			);

	checker->addInnerDeclaration( 
			_caseExpressionWire
		,	regenerateExpression( _case.getCaseExpression() )
		,	calculateBitwidth( _case.getCaseExpression() )
	);

	checker->setTestExpression(
			Tools::fillTemplate( CheckExpressionWire, m_currentSuspectNumber )
		,	Tools::fillTemplate( CheckExpression, _caseItems )
		,	_case.getItemsCount()
	);	
	checker->setFire( Tools::fillTemplate( FireWire, m_currentSuspectNumber ) );
	checker->setWidth( _case.getItemsCount() );
	checker->setMessage( Message );

	setControls( *checker );

	return checker;
}

/***************************************************************************/

}