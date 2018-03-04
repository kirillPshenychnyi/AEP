#include "stdafx.h"

#include "vlog_data_model\api\vlog_dm_conditional_statement.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_branch.hpp"
#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"

#include "vlog_data_model\sources\regenerators\vlog_dm_statement_regenerator.hpp"
#include "vlog_data_model\sources\regenerators\vlog_dm_expression_regenerator.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators {

/***************************************************************************/

StatementRegenerator::StatementRegenerator( std::ostream & _target )
	:	BaseRegenerator( _target )
{
}

/***************************************************************************/

void 
StatementRegenerator::visit( ConditionalStatement const & _statement )
{
	ExpressionRegenerator expressionRegenerator( m_targetStream, true );

	const int branchesCount = _statement.getBranchesCount();

	for( int i = 0; i < branchesCount; ++i )
	{
		if( i != 0 )
			m_targetStream << std::endl;

		ConditionalBranch const & branch = _statement.getBranch( i );
	
		if( i != 0 )
			m_targetStream << "else ";

		if( auto condition = branch.getCondition() )
		{
			m_targetStream << "if( ";
			condition->accept( expressionRegenerator );
			m_targetStream << " ) ";
		}
	
		m_targetStream << std::endl;
		branch.getStatement().accept( *this );
	}
}

/***************************************************************************/

void 
StatementRegenerator::visit( BlockingAssignment const & _assignment )
{
	ExpressionRegenerator expressionRegenerator( m_targetStream );

	_assignment.getAssignment().accept( expressionRegenerator );

	m_targetStream << ";";
}

/***************************************************************************/

}
}