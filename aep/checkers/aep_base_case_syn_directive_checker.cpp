#include "stdafx.h"

#include "aep\checkers\aep_base_case_syn_directive_checker.hpp"
#include "aep\api\aep_iaccessor.hpp"

#include "aep_model\api\aep_model_iaccessor.hpp"
#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_builder.hpp"

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
	,	m_caseStmtQuery(
				std::bind( 
						&BaseCaseSynDirectiveChecker::onCaseStatement
					,	this
					,	std::placeholders::_1 
				)
			,	std::bind( 
						&BaseCaseSynDirectiveChecker::isCheckableCase
					,	this
					,	std::placeholders::_1 
				)
		)
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
	m_caseStmtQuery.query( _process );
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

	AssertionContext & context = retrieveAssertionContext();

	bool isLast = false;
	for( int i = 0; i < nCaseItems; ++i )
	{
		isLast = i == nCaseItems - 1;
		
		auto castResult = itemCast.cast( _case.getItem( i ) );

		processExpressionItems( caseExpressionWire, checkTerms, *castResult, context );

		if( !isLast )
			checkTerms << getSeparator();
	}

	auto checker = getOvlChecker( _case, checkTerms.str(), caseExpressionWire );

	setEnable( context, m_caseStmtQuery, *checker );

	addInputPorts( _case.getCaseExpression(), context );

	context.addChecker( checker->releaseChecker() );

	m_currentSuspectNumber++;
}

/***************************************************************************/

void 
BaseCaseSynDirectiveChecker::processExpressionItems( 
		std::string const & _caseExpression
	,	std::stringstream & _ostream
	,	VlogDM::CaseItem const & _item 
	,	AepModel::AssertionContext & _context
)
{	
	const int nExpressions = _item.getExpressionsCount();
	bool isLast = false;
	for( int i = 0; i < nExpressions; ++i )
	{
		VlogDM::Expression const & expression = _item.getExpression( i );

		addInputPorts( expression, _context );

		isLast = i == nExpressions - 1;

		if( !isLast )
			_ostream << getSeparator();

		 _ostream << Tools::fillTemplate( 
							getCheckTerm()
						,	_caseExpression
						,	regenerateExpression( expression ) 
					);
	}
}

/***************************************************************************/

}