#ifndef __VLOG_DM_UNARY_OPERATOR_IMPL_HPP__
#define __VLOG_DM_UNARY_OPERATOR_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_unary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class UnaryOperatorImpl
	:	public LocatedImpl< UnaryOperator >
{

/***************************************************************************/

	typedef
		LocatedImpl< UnaryOperator >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	UnaryOperatorImpl( 
			ExpressionPtr _operand 
		,	Operator::Kind _operator
		,	Location const & _location
	);

/***************************************************************************/

	Expression const & getOperand() const final;

	Operator::Kind getOperator() const final;

	void accept( ExpressionVisitor & _visitor ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	ExpressionPtr m_operand;
	
	Operator::Kind m_operator;

/***************************************************************************/

};

/***************************************************************************/

inline 
UnaryOperatorImpl::UnaryOperatorImpl(
		ExpressionPtr _operand
	,	Operator::Kind _operator
	,	Location const & _location
	)
	:	BaseClass( _location )
	,	m_operand( std::move( _operand ) )
	,	m_operator( _operator )
{
}

/***************************************************************************/

inline
Expression const & 
UnaryOperatorImpl::getOperand() const
{
	assert( m_operand );

	return *m_operand;
}

/***************************************************************************/

Operator::Kind 
UnaryOperatorImpl::getOperator() const
{
	return m_operator;
}

/***************************************************************************/

inline 
void 
UnaryOperatorImpl::accept( ExpressionVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_UNARY_OPERATOR_IMPL_HPP__
