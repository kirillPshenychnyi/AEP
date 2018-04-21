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
#include "vlog_data_model\api\vlog_dm_case_item_cast.hpp"
#include "vlog_data_model\api\vlog_dm_case_item.hpp"

#include "vlog_data_model\api\vlog_dm_location.hpp"

#include <boost\format.hpp>
#include <sstream>

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
	using namespace VlogDM;
	using namespace AepModel;
	using namespace Resources::FullCaseSynDirecriveChecker;

	AepModel::IAccessor const & aepAccessor = m_accessor.getAepModel();

	std::unique_ptr< OvlAlwaysCheckerBuilder > checker 
		=	aepAccessor.getCheckersFactory().newOvlAlwaysChecker(
				( boost::format( CheckerInstanceName ) % m_detectedSuspects ).str()
				,	_case.getLocation().m_file
				,	_case.getLocation().m_beginLine
			);

	std::string caseExpression = regenerateExpression( _case.getCaseExpression() );

	const int nCaseItems = _case.getItemsCount();

	CaseItemCast< CaseItem > itemCast;
	
	std::stringstream checkTerms;

	bool isLast = false;
	for( int i = 0; i < nCaseItems; ++i )
	{
		isLast = i == nCaseItems - 1;

		auto castResult = itemCast.cast( _case.getItem( i ) );

		regenerateExpressionItems( caseExpression, checkTerms, *castResult );
		 
		if( !isLast )
			checkTerms << OrItem;
	}

	checker->setTestExpression(
			( boost::format( CheckExpressionWire ) % m_detectedSuspects ).str()
		,	( boost::format( CheckExpression ) % checkTerms.str() ).str()
		,	calculateBitwidth( _case.getCaseExpression() )
	);

	retrieveAssertionContext().addChecker( checker->releaseChecker() );

	m_detectedSuspects++;
}

/***************************************************************************/

void
FullCaseSynDirectiveChecker::regenerateExpressionItems( 
		std::string const & _caseExpression
	,	std::stringstream & _ostream
	,	VlogDM::CaseItem const & _item 
)
{
	using namespace Resources::FullCaseSynDirecriveChecker;
	
	const int nExpressions = _item.getExpressionsCount();
	bool isLast = false;
	for( int i = 0; i < nExpressions; ++i )
	{
		isLast = i == nExpressions - 1;

		if( !isLast )
			_ostream << OrItem;

		 _ostream << 
				( 
					boost::format( CheckTerm ) 
					%	_caseExpression
					%	regenerateExpression( _item.getExpression( i ) ) 
				).str();
	}
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