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

	void visit( const PrimaryLiteral& _literal ) override;

	void visit( const BinaryOperator& _operator ) override;
	 
	void visit( const PrimaryIdentifier& _id ) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // __VLOG_DM_EXPRESSION_REGENERATOR_HPP__

/***************************************************************************/