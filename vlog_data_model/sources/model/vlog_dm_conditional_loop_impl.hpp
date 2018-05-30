#ifndef __VLOG_DM_CONDITIONAL_LOOP_IMPL_HPP__
#define __VLOG_DM_CONDITIONAL_LOOP_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_loop_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

template< typename _TLoop >
class ConditionalLoopImpl
	:	public LoopImpl< _TLoop >
{

/***************************************************************************/

	typedef
		LoopImpl< _TLoop >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	ConditionalLoopImpl(
			Location const & _location
		,	StatementPtr _loopStmt
		,	ExpressionPtr _condition
	);

	virtual ~ConditionalLoopImpl() = default;

	Expression const & getCondition() const;

/***************************************************************************/

private:

/***************************************************************************/

	ExpressionPtr m_condition;

/***************************************************************************/

};

/***************************************************************************/

template< typename _TLoop >
inline 
ConditionalLoopImpl< _TLoop >::ConditionalLoopImpl( 
		Location const & _location
	,	StatementPtr _loopStmt
	,	ExpressionPtr _condition 
	)	
	:	BaseClass( _location, std::move( _loopStmt ) )
	,	m_condition( std::move( _condition ) )
{
}

/***************************************************************************/

template< typename _TLoop >
inline 
Expression const &
ConditionalLoopImpl< _TLoop >::getCondition() const
{
	assert( m_condition );
	return *m_condition;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONDITIONAL_LOOP_IMPL_HPP__
