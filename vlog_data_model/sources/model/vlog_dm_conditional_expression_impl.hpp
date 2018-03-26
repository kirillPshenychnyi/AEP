#ifndef __VLOG_DM_CONDITIONAL_EXPRESSION_HPP_IMPL__
#define __VLOG_DM_CONDITIONAL_EXPRESSION_HPP_IMPL__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_conditional_expression.hpp"
#include "vlog_data_model\api\vlog_dm_expression_cast.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ConditionalExpressionImpl
	:	public LocatedImpl< ConditionalExpression >
{

/***************************************************************************/

	typedef
		LocatedImpl< ConditionalExpression >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	ConditionalExpressionImpl(
			Location const & _location
		,	ExpressionPtr _condition
		,	ExpressionPtr _trueBranch
		,	ExpressionPtr _falseBranch
	);

/***************************************************************************/

	Expression const & getCondition() const final;

	Expression const & getTrueBranch() const final;

	Expression const & getFalseBranch() const final;

	void accept( ExpressionVisitor & _visitor ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	ExpressionPtr m_condition;
	
	ExpressionPtr m_trueBranch;
	
	ExpressionPtr m_falseBranch;

/***************************************************************************/

};

/***************************************************************************/

ConditionalExpressionImpl::ConditionalExpressionImpl(
		Location const & _location
	,	ExpressionPtr _condition
	,	ExpressionPtr _trueBranch
	,	ExpressionPtr _falseBranch
	)
	:	BaseClass( _location )
	,	m_condition( std::move( _condition ) )
	,	m_trueBranch( std::move( _trueBranch ) )
	,	m_falseBranch( std::move( _falseBranch ) )
{
}

/***************************************************************************/

inline 
Expression const & 
ConditionalExpressionImpl::getCondition() const
{
	assert( m_condition );

	return *m_condition;
}

/***************************************************************************/

inline 
Expression const & 
ConditionalExpressionImpl::getTrueBranch() const
{
	assert( m_trueBranch );

	return *m_trueBranch;
}

/***************************************************************************/

inline 
Expression const & 
ConditionalExpressionImpl::getFalseBranch() const
{
	assert( m_falseBranch );

	return *m_falseBranch;
}

/***************************************************************************/

inline 
void 
ConditionalExpressionImpl::accept( ExpressionVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONDITIONAL_EXPRESSION_HPP_IMPL__
