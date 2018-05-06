#ifndef __VLOG_DM_DECLARATION_VISITOR_HPP__
#define __VLOG_DM_DECLARATION_VISITOR_HPP__

/***************************************************************************/

#include "common_tools\utils\visitor_cast.hpp"

/***************************************************************************/

namespace VlogDM{

/***************************************************************************/

struct PortDeclaration;
struct VariableDeclaration;

/***************************************************************************/

struct DeclarationVisitor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void visit( PortDeclaration const& _port ) = 0;

	virtual void visit( VariableDeclaration const& _var ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct DeclarationDefaultVisitor
	:	public DeclarationVisitor
{

/***************************************************************************/

	void visit( PortDeclaration const& _port ) override {}

	void visit( VariableDeclaration const& _var ) override {}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // __VLOG_DM_DECLARATION_VISITOR_HPP__