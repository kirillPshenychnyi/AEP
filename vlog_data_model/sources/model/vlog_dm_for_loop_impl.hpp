#ifndef __VLOG_DM_FOR_LOOP_IMPL_HPP__
#define __VLOG_DM_FOR_LOOP_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_for_loop.hpp"

#include "vlog_data_model\sources\model\vlog_dm_loop_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ForLoopImpl
	:	public LoopImpl< ForLoop >
{

/***************************************************************************/

	typedef
		LoopImpl< ForLoop >
		BaseClass;

	typedef
		std::unique_ptr< BinaryOperator >
		BinaryOperatorPtr;

/***************************************************************************/

public:

/***************************************************************************/

	ForLoopImpl(
			Location const & _location
		,	StatementPtr _loopStatement
		,	BinaryOperatorPtr _initialization
		,	ExpressionPtr _condition
		,	BinaryOperatorPtr _iteration
	);

/***************************************************************************/

	Expression const & getInitialization() const final;

	Expression const & getCondition() const final;

	BinaryOperator const & getIteration() const final;

/***************************************************************************/

private:

/***************************************************************************/

	BinaryOperatorPtr m_initialization;
	
	ExpressionPtr m_condition;

	BinaryOperatorPtr m_iteration;

/***************************************************************************/

};

/***************************************************************************/

inline
ForLoopImpl::ForLoopImpl(
		Location const & _location
	,	StatementPtr _loopStatement
	,	BinaryOperatorPtr _initialization
	,	ExpressionPtr _condition
	,	BinaryOperatorPtr _iteration
	)
	:	BaseClass( _location, std::move( _loopStatement ) )
	,	m_initialization( std::move( _initialization ) )
	,	m_condition( std::move( _condition ) )
	,	m_iteration( std::move( _iteration ) )
{
}


/***************************************************************************/

inline 
Expression const & 
ForLoopImpl::getInitialization() const
{
	assert( m_initialization );

	return *m_initialization;
}

/***************************************************************************/

inline 
Expression const & 
ForLoopImpl::getCondition() const
{
	assert( m_condition );

	return *m_condition;
}

/***************************************************************************/

inline 
BinaryOperator const & 
ForLoopImpl::getIteration() const
{
	assert( m_iteration );

	return *m_iteration;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_FOR_LOOP_IMPL_HPP__
