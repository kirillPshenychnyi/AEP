#include "stdafx.h"

#include "aep\checkers\aep_base_case_syn_directive_checker.hpp"
#include "aep\api\aep_iaccessor.hpp"
#include "aep\utils\aep_utils_statement_query.hpp"

#include "aep_model\api\aep_model_iaccessor.hpp"
#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"

#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"
#include "vlog_data_model\api\vlog_dm_case_statement.hpp"
#include "vlog_data_model\api\vlog_dm_case_statement.hpp"
#include "vlog_data_model\api\vlog_dm_case_item_cast.hpp"
#include "vlog_data_model\api\vlog_dm_case_item.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include "common_tools\utils\string_utils.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

BaseCaseSynDirectiveChecker::BaseCaseSynDirectiveChecker( 
		IAccessor & _accessor 
)
	:	BaseAepChecker( _accessor )
{
}

/***************************************************************************/

void 
BaseCaseSynDirectiveChecker::analyze()
{
	browseProcesses< VlogDM::BehavioralProcess >(
		std::bind( 
				&BaseCaseSynDirectiveChecker::onProcess
			,	this
			,	std::placeholders::_1 
		)
	);
}

/***************************************************************************/

void
BaseCaseSynDirectiveChecker::onProcess( VlogDM::BehavioralProcess const & _process )
{
	Utils::StatementQuery< VlogDM::CaseStatement > caseStmtQuery(
			_process
		,	std::bind( 
					&BaseCaseSynDirectiveChecker::onCaseStatement
				,	this
				,	std::placeholders::_1 
			)
		,	std::bind( 
					&BaseCaseSynDirectiveChecker::isCheckableCase
				,	this
				,	std::placeholders::_1 
			)
	);

	caseStmtQuery.query();
}

/***************************************************************************/

void 
BaseCaseSynDirectiveChecker::onCaseStatement( 
	VlogDM::CaseStatement const & _case 
)
{
	using namespace VlogDM;
	using namespace AepModel;

	std::string caseExpressionWire 
		=	Tools::fillTemplate( 
					getSelWireName()
				,	_case.getLocation().m_beginLine 
			);

	const int nCaseItems = _case.getItemsCount();

	CaseItemCast< CaseItem > itemCast;
	
	std::stringstream checkTerms;

	bool isLast = false;
	for( int i = 0; i < nCaseItems; ++i )
	{
		isLast = i == nCaseItems - 1;
		
		auto castResult = itemCast.cast( _case.getItem( i ) );

		regenerateExpressionItems( caseExpressionWire, checkTerms, *castResult );

		if( !isLast )
			checkTerms << getSeparator();
	}

	AssertionContext & context = retrieveAssertionContext();

	int caseExpressionWidth = calculateBitwidth( _case.getCaseExpression() );

	context.addInputPort( 
			caseExpressionWire
		,	regenerateExpression( _case.getCaseExpression() )
		,	caseExpressionWidth 
	);

	context.addChecker( getOvlChecker( _case, checkTerms.str() ) );

	m_currentSuspectNumber++;
}

/***************************************************************************/

void 
BaseCaseSynDirectiveChecker::regenerateExpressionItems( 
		std::string const & _caseExpression
	,	std::stringstream & _ostream
	,	VlogDM::CaseItem const & _item 
)
{	
	const int nExpressions = _item.getExpressionsCount();
	bool isLast = false;
	for( int i = 0; i < nExpressions; ++i )
	{
		isLast = i == nExpressions - 1;

		if( !isLast )
			_ostream << getSeparator();

		 _ostream << Tools::fillTemplate( 
							getCheckTerm()
						,	_caseExpression
						,	regenerateExpression( _item.getExpression( i ) ) 
					);
	}
}

/***************************************************************************/

}