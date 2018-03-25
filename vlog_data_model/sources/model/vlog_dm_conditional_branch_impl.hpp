#ifndef __VLOG_DM_CONDITIONAL_BRANCH_IMPL_HPP__
#define __VLOG_DM_CONDITIONAL_BRANCH_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_conditional_branch.hpp"
#include "vlog_data_model\api\vlog_dm_statement.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"
#include "common_tools\utils\convertors.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ConditionalBranchImpl
	:	public LocatedImpl< ConditionalBranch >
{

/***************************************************************************/

	typedef
		LocatedImpl< ConditionalBranch >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	ConditionalBranchImpl(
			ExpressionPtr _condtion
		,	StatementPtr _statement
	);

/***************************************************************************/

	boost::optional< Expression const & > getCondition () const final;

	Statement const & getStatement() const final;

/***************************************************************************/

private:

/***************************************************************************/

	ExpressionPtr m_condition;
	StatementPtr m_statement;

/***************************************************************************/

};

/***************************************************************************/

ConditionalBranchImpl::ConditionalBranchImpl(
		ExpressionPtr _condition
	,	StatementPtr _statement
	)
	:	BaseClass( _condition ? _condition->getLocation() : _statement->getLocation() )
	,	m_condition( std::move( _condition ) )
	,	m_statement( std::move( _statement ) )
{}

/***************************************************************************/

boost::optional< Expression const& > 
ConditionalBranchImpl::getCondition() const
{
	return Tools::Convertors::convertPointerToOptional( m_condition.get() );
}

/***************************************************************************/

Statement const & 
ConditionalBranchImpl::getStatement() const
{
	assert( m_statement );

	return *m_statement;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONDITIONAL_BRANCH_IMPL_HPP__
