#ifndef __VLOG_DM_EXPRESSION_IMPL_HPP__
#define _VLOG_DM_EXPRESSION_IMPL_HPP__

/***************************************************************************/

#include "api\vlog_dm_expression_visitor.hpp"

#include "sources\model\vlog_dm_located_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

template< typename _TBase >
class ExpressionImpl
	: public LocatedImpl< _TBase >
{

/***************************************************************************/

	virtual ~ExpressionImpl() {}

	void accept( ExpressionVisitor const & _visitor ) override const;

/***************************************************************************/

};

/***************************************************************************/

template< typename _TBase >
inline 
void
ExpressionImpl< _TBase >::accept( ExpressionVisitor & _visitor ) const
{
	_visitor.accept( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_IMPL_HPP__
