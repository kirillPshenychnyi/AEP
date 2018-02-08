#ifndef __VLOG_DM_STATEMENT_HPP__
#define __VLOG_DM_STATEMENT_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct StatementVisitor;

/***************************************************************************/

struct Statement
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void accept( StatementVisitor & _visitor ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_STATEMENT_HPP__
