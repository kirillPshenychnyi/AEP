#include "stdafx.h"

#include "aep\utils\aep_utils_condition_regenerator.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_statement.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_branch.hpp"
#include "vlog_data_model\api\vlog_dm_case_statement.hpp"
#include "vlog_data_model\api\vlog_dm_case_item.hpp"
#include "vlog_data_model\api\vlog_dm_case_item_cast.hpp"

#include "common_tools\utils\string_utils.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils { 

/***************************************************************************/

ConditionRegenerator::ConditionRegenerator( 
		VlogDM::IAccessor const & _vlogDm
	,	VlogDM::Statement const & _stmt 
	,	int _branch 
)
	:	m_vlogDm( _vlogDm )
	,	m_stmt( _stmt )
	,	m_branchIdx( _branch )
{
}

/***************************************************************************/

void 
ConditionRegenerator::run()
{
	m_stmt.accept( *this );
}

/***************************************************************************/

void
ConditionRegenerator::visit( VlogDM::ConditionalStatement const & _cond )
{
	static const char * const s_logicAnd = " && ";

	createInvertedCondition(
			_cond
		,	m_branchIdx 
		,	[ & ]( int _idx ) -> VlogDM::Expression const & 
			{ 
				return *_cond.getBranch( _idx ).getCondition(); 
			}
		,	std::bind( 
					&VlogDM::IAccessor::regenerateExpression 
				,	std::ref( m_vlogDm )
				,	std::placeholders::_1
			)
	);
	
	if( auto condition = _cond.getBranch( m_branchIdx ).getCondition() )
	{
		m_collected.push_back( condition.get_ptr() );

		std::string const regenerated = m_vlogDm.regenerateExpression( *condition );

		if( !m_result.empty() )
			m_result.append( s_logicAnd );

		m_result.append( regenerated );
	}
}

/***************************************************************************/

void
ConditionRegenerator::visit( VlogDM::CaseStatement const & _case )
{
	using namespace VlogDM;

	CaseItemCast< CaseItem > itemCaster;

	static const char * const s_term = "%1% == %2%";
	static const char * const s_or = " || ";

	BaseCaseItem const& branch = _case.getItem( m_branchIdx );

	auto caseItem = itemCaster.cast( branch );

	if( !caseItem )
		return;

	m_collected.push_back( &_case.getCaseExpression() );

	std::string const caseExpr{ m_vlogDm.regenerateExpression( _case.getCaseExpression() ) };

	const int nExpressions = caseItem->getExpressionsCount();

	for( int i = 0; i < nExpressions; ++i )
	{
		Expression const & caseItemExpression = caseItem->getExpression( i );

		m_collected.push_back( &caseItemExpression );

		if( !m_result.empty() )
			m_result.append( s_or );

		m_result.append(
			Tools::fillTemplate( 
					s_term
				,	caseExpr
				,	m_vlogDm.regenerateExpression( caseItemExpression ) 
			)
		);
	}
}

/***************************************************************************/

template< typename _TStmt >
void 
ConditionRegenerator::createInvertedCondition(
		_TStmt const & _stmt
	,	int _nBranches
	,	std::function< VlogDM::Expression const &( int ) > _conditionGetter
	,	std::function< std::string( VlogDM::Expression const & ) > _conditionRegenerator
)
{
	static const char * const s_invTerm = "!%1%";
	static const char * const s_logicAnd = " && ";

	for( int i = 0; i < _nBranches; ++i )
	{
		VlogDM::Expression const & expression = _conditionGetter( i );

		m_collected.push_back( &expression );

		if( !m_result.empty() )
			m_result.append( s_logicAnd );

		m_result.append(
			Tools::fillTemplate( s_invTerm, _conditionRegenerator( expression ) )
		);
	}
}

/***************************************************************************/

}
}

