#ifndef __VLOG_DM_CONDITIONAL_BRANCH_IMPL_HPP__
#define __VLOG_DM_CONDITIONAL_BRANCH_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_conditional_branch.hpp"
#include "vlog_data_model\api\vlog_dm_statement.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

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
		,	Location const & _location
	);

/***************************************************************************/

	boost::optional< Expression const & > getCondition () const override;

	Statement const & getStatement() const override;

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
	,	Location const & _location
	)
	:	BaseClass( _location )
	,	m_condition( std::move( _condition ) )
	,	m_statement( std::move( _statement ) )
{}

/***************************************************************************/

boost::optional< Expression const& > 
ConditionalBranchImpl::getCondition() const
{
	assert( m_condition );

	return *m_condition;
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
