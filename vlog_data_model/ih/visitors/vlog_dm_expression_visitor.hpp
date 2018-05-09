#ifndef __VLOG_DM_EXPRESSION_VISITOR_HPP__
#define __VLOG_DM_EXPRESSION_VISITOR_HPP__

/***************************************************************************/

#include "common_tools\utils\declare_visitors.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Expression;
struct PrimaryLiteral;
struct PrimaryIdentifier;
struct BinaryOperator;
struct UnaryOperator;
struct Concatenation;
struct MultipleConcatenation;
struct ConditionalExpression;

/***************************************************************************/

DECLARE_VISITORS(
		Expression
	,	PrimaryLiteral
	,	PrimaryIdentifier
	,	BinaryOperator
	,	UnaryOperator
	,	Concatenation
	,	MultipleConcatenation
	,	ConditionalExpression
)

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_VISITOR_HPP__
