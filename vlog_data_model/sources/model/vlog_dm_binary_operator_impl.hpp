#ifndef __VLOG_DM_BINARY_OPERATOR_IMPL_HPP__
#define __VLOG_DM_BINARY_OPERATOR_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

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
		,	Operator::Enum _operator
	);

/***************************************************************************/

	Expression const & getLeftOperand() const override;

	Expression const & getRightOperand() const override;

	Operator::Enum getOperator() const override;

	void accept( ExpressionVisitor & _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	ExpressionPtr m_leftOperand;
	ExpressionPtr m_rightOperand;
	Operator::Enum m_operator;

/***************************************************************************/

};

/***************************************************************************/

inline
BinaryOperatorImpl::BinaryOperatorImpl(
		Location const & _location
	,	std::unique_ptr< Expression > _leftOperand
	,	std::unique_ptr< Expression > _rightOperand
	,	Operator::Enum _operator
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
	return *m_leftOperand;
}

/***************************************************************************/

inline
Expression const &
BinaryOperatorImpl::getRightOperand() const
{
	return *m_rightOperand;
}

/***************************************************************************/

inline 
Operator::Enum
BinaryOperatorImpl::getOperator() const
{
	return m_operator;
}

/***************************************************************************/

void 
BinaryOperatorImpl::accept( ExpressionVisitor & _visitor ) const
{
	
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_BINARY_OPERATOR_IMPL_HPP__
