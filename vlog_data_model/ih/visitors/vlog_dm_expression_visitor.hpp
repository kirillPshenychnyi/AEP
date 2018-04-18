#ifndef __VLOG_DM_EXPRESSION_VISITOR_HPP__
#define __VLOG_DM_EXPRESSION_VISITOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

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

struct ExpressionVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( PrimaryLiteral const & _literal ) = 0;

	virtual void visit( BinaryOperator const & _operator ) = 0;
	
	virtual void visit( UnaryOperator const & _operator ) = 0;

	virtual void visit( PrimaryIdentifier const & _id ) = 0;

	virtual void visit( Concatenation const & _concat ) = 0;

	virtual void visit( MultipleConcatenation const & _concat ) = 0;

	virtual void visit( ConditionalExpression const & _conditional ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct ExpressionDefaultVisitor
	:	public ExpressionVisitor
{

/***************************************************************************/

	void visit( PrimaryLiteral const& _literal ) override {}

	void visit( BinaryOperator const& _operator ) override {}

	void visit( UnaryOperator const& _operator ) override {}

	void visit( PrimaryIdentifier const& _id ) override {}

	void visit( Concatenation const& _id ) override {}

	void visit( MultipleConcatenation const & _concat ) override {}

	void visit( ConditionalExpression const & _conditional ) override {}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_VISITOR_HPP__
