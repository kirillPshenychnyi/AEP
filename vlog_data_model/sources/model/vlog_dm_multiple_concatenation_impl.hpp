#ifndef __VLOG_DM_MULTIPLE_CONCATENATION_IMPL_HPP__
#define __VLOG_DM_MULTIPLE_CONCATENATION_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_multiple_concatenation.hpp"
#include "vlog_data_model\api\vlog_dm_concatenation.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class MultipleConcatenationImpl
	:	public LocatedImpl< MultipleConcatenation >
{

/***************************************************************************/

	typedef
		LocatedImpl< MultipleConcatenation >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	MultipleConcatenationImpl( 
			ConcatPtr _concat
		,	ExpressionPtr _repeatExpression
		,	Location const & _location
	);

/***************************************************************************/

	Concatenation const & getConcatenation() const override;
	
	Expression const & getRepeatExpression() const override;

	void accept( ExpressionVisitor & _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	ConcatPtr m_concat;
	ExpressionPtr m_repeatExpression;

/***************************************************************************/

};

/***************************************************************************/

MultipleConcatenationImpl::MultipleConcatenationImpl(
		ConcatPtr _concat
	,	ExpressionPtr _repeatExpression
	,	Location const & _location
	)
	:	BaseClass( _location )
	,	m_concat( std::move( _concat ) )
	,	m_repeatExpression( std::move( _repeatExpression ) )
{
}

/***************************************************************************/

inline 
Concatenation const & 
MultipleConcatenationImpl::getConcatenation() const
{
	assert( m_concat );

	return *m_concat;
}

/***************************************************************************/

inline 
Expression const & 
MultipleConcatenationImpl::getRepeatExpression() const
{
	assert( m_repeatExpression );

	return *m_repeatExpression;
}

/***************************************************************************/

inline
void 
MultipleConcatenationImpl::accept( ExpressionVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_MULTIPLE_CONCATENATION_IMPL_HPP__
