#ifndef __AEP_UTILS_EXPRESSION_QUERY_HPP__
#define __AEP_UTILS_EXPRESSION_QUERY_HPP__

/***************************************************************************/

#include "aep\sources\utils\aep_utils_base_query.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"
#include "vlog_data_model\api\vlog_dm_expression_cast.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

template< typename _TTarget >
class ExpressionQuery
	:	public BaseQuery< _TTarget, VlogDM::ExpressionCast >
	,	public VlogDM::ExpressionVisitor
	
{

/***************************************************************************/

	using BaseClass = BaseQuery< _TTarget, VlogDM::ExpressionCast >;

	using Query = ExpressionQuery< _TTarget >;

/***************************************************************************/

public:

/***************************************************************************/

	ExpressionQuery( ConstructCallback && _callback );

	void query( VlogDM::ContinuousAssignment const & _process );

	void query( VlogDM::BehavioralProcess const & _process );

	void query( VlogDM::Expression const & _expression );

/***************************************************************************/

private:

/***************************************************************************/

	void visit( const VlogDM::PrimaryLiteral& _literal ) final;
	
	void visit( const VlogDM::PrimaryIdentifier& _id ) final;
	
	void visit( const VlogDM::BinaryOperator& _binary ) final;
	
	void visit( const VlogDM::UnaryOperator& _unary ) final;

	void visit( const VlogDM::Concatenation& _concat ) final;

	void visit( const VlogDM::MultipleConcatenation& _concat ) final;
	
	void visit( const VlogDM::ConditionalExpression& _condExpression ) final;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__AEP_UTILS_EXPRESSION_QUERY_HPP__
