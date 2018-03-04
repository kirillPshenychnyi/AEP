#include "stdafx.h"

#include "vlog_data_model\sources\regenerators\vlog_dm_process_regenerator.hpp"
#include "vlog_data_model\sources\regenerators\vlog_dm_expression_regenerator.hpp"
#include "vlog_data_model\sources\regenerators\vlog_dm_statement_regenerator.hpp"

#include "vlog_data_model\api\vlog_dm_statement.hpp"
#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"
#include "vlog_data_model\api\vlog_dm_sensitivity_list.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators{ 

/***************************************************************************/

ProcessRegenerator::ProcessRegenerator( std::ostream & _targetStream )
	:	BaseRegenerator( _targetStream )
{
}

/***************************************************************************/

void 
ProcessRegenerator::visit( ContinuousAssignment const & _assing )
{
	m_targetStream << "assign ";

	ExpressionRegenerator expressionRegenerator( m_targetStream );

	_assing.getAssignment().accept( expressionRegenerator );

	m_targetStream << ";";
}

/***************************************************************************/

void 
ProcessRegenerator::visit( BehavioralProcess const & _behavioral )
{
	StatementRegenerator statementRegenerator( m_targetStream );

	m_targetStream << "always@( ";
	if( auto sensitivityList = _behavioral.getSensitivityList() )
	{
		ExpressionRegenerator exprRegenerator( m_targetStream, true );

		const int expressionsCount = sensitivityList->getExpressionsCount();

		for( int i = 0; i < expressionsCount; ++i )
		{
			sensitivityList->getExpression( i ).accept( exprRegenerator );

			if( i != expressionsCount - 1 )
				m_targetStream << ", ";
		}
	}
	else
	{
		m_targetStream << "*";
	}

	m_targetStream << " )";

	m_targetStream << "\n";
	_behavioral.getStatement().accept( statementRegenerator );
}

/***************************************************************************/

}
}