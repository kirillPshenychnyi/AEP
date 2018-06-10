#include "stdafx.h"

#include "aep\sources\utils\aep_utils_expression_query.hpp"
#include "aep\sources\utils\aep_utils_expression_extractor.hpp"

#include "vlog_data_model\api\vlog_dm_expression_cast.hpp"
#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"
#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_unary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_concatenation.hpp"
#include "vlog_data_model\api\vlog_dm_multiple_concatenation.hpp"
#include "vlog_data_model\api\vlog_dm_conditional_expression.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

template< typename _TTarget >
ExpressionQuery< _TTarget >::ExpressionQuery( ConstructCallback && _callback )
	:	BaseClass( std::forward< ConstructCallback >( _callback ) )
{
}

/***************************************************************************/

template< typename _TTarget >
void
ExpressionQuery< _TTarget >::query( VlogDM::ContinuousAssignment const & _assign )
{
	_assign.getAssignment().accept( *this );
}

/***************************************************************************/

template< typename _TTarget >
void
ExpressionQuery< _TTarget >::query( VlogDM::BehavioralProcess const & _process )
{
	ExpressionExtractor expressionExtractor( 
			std::bind(
					&VlogDM::Expression::accept
				,	std::placeholders::_1
				,	std::ref( *this )
			)
		,	*this
	);

	_process.getStatement().accept( expressionExtractor );
}

/***************************************************************************/

template< typename _TTarget >
void 
ExpressionQuery< _TTarget >::query( VlogDM::Expression const & _expression )
{
	_expression.accept( *this );
}

/***************************************************************************/

template<typename _TTarget>
void 
ExpressionQuery< _TTarget >::visit( const VlogDM::PrimaryLiteral & _literal )
{
	processAsTargetConstruct( _literal );
}

/***************************************************************************/

template< typename _TTarget >
void 
ExpressionQuery< _TTarget >::visit( const VlogDM::PrimaryIdentifier & _id )
{
	processAsTargetConstruct( _id );
}

/***************************************************************************/

template< typename _TTarget >
void 
ExpressionQuery< _TTarget >::visit( const VlogDM::BinaryOperator & _binary )
{
	processAsTargetConstruct( _binary );

	_binary.getLeftOperand().accept( *this );
	_binary.getRightOperand().accept( *this );
}

/***************************************************************************/

template< typename _TTarget >
void 
ExpressionQuery< _TTarget >::visit( const VlogDM::UnaryOperator & _unary )
{
	processAsTargetConstruct( _unary );
	_unary.getOperand().accept( *this );
}

/***************************************************************************/

template< typename _TTarget >
void 
ExpressionQuery< _TTarget >::visit( const VlogDM::Concatenation & _concat )
{
	processAsTargetConstruct( _concat );
	
	processAsConstructsContainer< Query, VlogDM::Expression >( 
			_concat.getExpressionsCount()
		,	[ & ]( int _idx ) -> VlogDM::Expression const &
			{
				return _concat.getExpression( _idx );
			}
		,	*this
	);
}

/***************************************************************************/

template< typename _TTarget >
void 
ExpressionQuery< _TTarget >::visit( const VlogDM::MultipleConcatenation & _concat )
{
	processAsTargetConstruct( _concat );

	_concat.getRepeatExpression().accept( *this );
	_concat.getConcatenation().accept( *this );
}

/***************************************************************************/

template< typename _TTarget >
void 
ExpressionQuery< _TTarget >::visit(
	const VlogDM::ConditionalExpression & _condExpression 
)
{
	auto processBranch
		=	[ & ]( VlogDM::Expression const & _branch, int _branchIdx )
			{
				//pushCondition( _condExpression, _branchIdx );
				processAsTargetConstruct( _branch );
				//popCondition();
			};
	
	processAsTargetConstruct( _condExpression );

	_condExpression.getCondition().accept( *this );
	
	processBranch( _condExpression.getTrueBranch(), 0 );
	processBranch( _condExpression.getFalseBranch(), 1 );
}

/***************************************************************************/

template class ExpressionQuery< VlogDM::PrimaryIdentifier >;

/***************************************************************************/

}
}