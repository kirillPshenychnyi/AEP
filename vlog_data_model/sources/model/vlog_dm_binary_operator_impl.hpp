#ifndef __VLOG_DM_BINARY_OPERATOR_IMPL_HPP__
#define __VLOG_DM_BINARY_OPERATOR_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class BinaryOperatorImpl
	:	public LocatedImpl< BinaryOperator >
{

/***************************************************************************/

	typedef
		LocatedImpl< BinaryOperator >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	BinaryOperatorImpl(
			Location const & _location
		,	ExpressionPtr _leftOperand
		,	ExpressionPtr _rightOperand
		,	Operator::Kind _operator
	);

/***************************************************************************/

	Expression const & getLeftOperand() const final;

	Expression const & getRightOperand() const final;

	Operator::Kind getOperator() const final;

	void accept( ExpressionVisitor & _visitor ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	ExpressionPtr m_leftOperand;
	ExpressionPtr m_rightOperand;
	Operator::Kind m_operator;

/***************************************************************************/

};

/***************************************************************************/

inline
BinaryOperatorImpl::BinaryOperatorImpl(
		Location const & _location
	,	std::unique_ptr< Expression > _leftOperand
	,	std::unique_ptr< Expression > _rightOperand
	,	Operator::Kind _operator
	)
	:	BaseClass( _location )
	,	m_leftOperand( _leftOperand.release() )
	,	m_rightOperand( _rightOperand.release() )
	,	m_operator( _operator )
{
}

/***************************************************************************/

inline
Expression const &
BinaryOperatorImpl::getLeftOperand() const
{
	assert( m_leftOperand );

	return *m_leftOperand;
}

/***************************************************************************/

inline
Expression const &
BinaryOperatorImpl::getRightOperand() const
{
	assert( m_rightOperand );

	return *m_rightOperand;
}

/***************************************************************************/

inline 
Operator::Kind
BinaryOperatorImpl::getOperator() const
{
	return m_operator;
}

/***************************************************************************/

inline
void 
BinaryOperatorImpl::accept( ExpressionVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_BINARY_OPERATOR_IMPL_HPP__
