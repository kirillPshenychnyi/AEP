#ifndef __VLOG_DM_CONCATENATION_IMPL_HPP__
#define __VLOG_DM_CONCATENATION_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_concatenation.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include <vector>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ConcatenationImpl
	:	public LocatedImpl< Writable::Concatenation >
{

/***************************************************************************/

	typedef
		LocatedImpl< Writable::Concatenation >
		BaseClass;

	typedef
		std::vector< ExpressionPtr >
		Expressions;

/***************************************************************************/

public:

/***************************************************************************/

	ConcatenationImpl( Location const& _location );

	void addExpression( ExpressionPtr _expressionPtr ) override;
	
	int getExpressionsCount() const override;

	Expression const & getExpression( int _idx  ) const override;

	void accept( ExpressionVisitor & _expressionVisitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	Expressions m_expressions;

/***************************************************************************/

};

/***************************************************************************/

inline
ConcatenationImpl::ConcatenationImpl( Location const & _location )
	:	BaseClass( _location )
{
}

/***************************************************************************/

inline
void
ConcatenationImpl::addExpression( ExpressionPtr _expressionPtr )
{
	m_expressions.push_back( std::move( _expressionPtr ) );
}

/***************************************************************************/

inline 
int
ConcatenationImpl::getExpressionsCount() const
{
	return m_expressions.size();
}

/***************************************************************************/

inline
Expression const & 
ConcatenationImpl::getExpression( int _idx ) const
{
	return *m_expressions[ _idx ];
}

/***************************************************************************/

void 
ConcatenationImpl::accept( ExpressionVisitor & _expressionVisitor ) const
{
	_expressionVisitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONCATENATION_IMPL_HPP__
