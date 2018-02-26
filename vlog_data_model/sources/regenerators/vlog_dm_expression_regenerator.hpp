#ifndef __VLOG_DM_EXPRESSION_REGENERATOR_HPP__
#define __VLOG_DM_EXPRESSION_REGENERATOR_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"

#include "vlog_data_model\sources\regenerators\vlog_dm_base_regenerator.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators {

/***************************************************************************/

struct ExpressionRegenerator
	:	public BaseRegenerator
	,	public ExpressionVisitor
{

/***************************************************************************/

public:

/***************************************************************************/

	ExpressionRegenerator( std::ostream & _targetStream );

/***************************************************************************/

private:

/***************************************************************************/

	void visit( PrimaryLiteral const& _literal ) override;

	void visit( BinaryOperator const& _operator ) override;
	
	void visit( UnaryOperator const& _operator ) override;
	
	void visit( PrimaryIdentifier const& _id ) override;

	void visit( Concatenation const& _concat ) override;

	void visit( MultipleConcatenation const& _concat ) override;

	void visit( ConditionalExpression const & _conditional ) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // __VLOG_DM_EXPRESSION_REGENERATOR_HPP__

/***************************************************************************/