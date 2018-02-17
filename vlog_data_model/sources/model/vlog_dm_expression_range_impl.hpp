#ifndef __VLOG_DM_EXPRESSION_RANGE_IMPL_HPP__
#define __VLOG_DM_EXPRESSION_RANGE_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_expression_range.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_range_visitor.hpp"

#include "vlog_data_model\api\vlog_dm_expression.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ExpressionRangeImpl
	:	public LocatedImpl< ExpressionRange >
{

/***************************************************************************/

	typedef
		LocatedImpl< ExpressionRange >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	ExpressionRangeImpl( ExpressionPtr _expression );

	Expression const & getExpression() const override;

	void accept( RangeVisitor & _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	ExpressionPtr m_expression;

/***************************************************************************/

};

/***************************************************************************/

inline
ExpressionRangeImpl::ExpressionRangeImpl( ExpressionPtr _expression )
	:	BaseClass( _expression->getLocation() )
	,	m_expression( std::move( _expression ) )
{
}

/***************************************************************************/

inline 
Expression const & 
ExpressionRangeImpl::getExpression() const
{
	return *m_expression;
}

/***************************************************************************/

void 
ExpressionRangeImpl::accept( RangeVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_RANGE_IMPL_HPP__
