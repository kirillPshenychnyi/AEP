#ifndef __VLOG_DM_CASE_ITEM_IMPL_HPP__
#define __VLOG_DM_CASE_ITEM_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_case_item_base_impl.hpp"

#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_case_item.hpp"

#include <vector>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class CaseItemImpl
	:	public CaseItemBaseImpl< Writable::CaseItem >
{

/***************************************************************************/

	typedef
		std::vector< ExpressionPtr >
		Expressions;

	typedef
		CaseItemBaseImpl< Writable::CaseItem >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	CaseItemImpl( Location const & _location );

/***************************************************************************/

	void addExpression( ExpressionPtr _expression ) override;

	Expression const & getExpression( int _idx ) const override;

	int getExpressionsCount() const override;

/***************************************************************************/

public:

/***************************************************************************/

	Expressions m_expressions;

/***************************************************************************/

};

/***************************************************************************/

inline 
CaseItemImpl::CaseItemImpl( Location const & _location )
	:	BaseClass( _location )
{
}

/***************************************************************************/

inline 
void 
CaseItemImpl::addExpression( ExpressionPtr _expression )
{
	m_expressions.push_back( std::move( _expression ) );
}

/***************************************************************************/

Expression const & 
CaseItemImpl::getExpression( int _idx ) const
{
	return *m_expressions[ _idx ];
}

/***************************************************************************/

inline 
int 
CaseItemImpl::getExpressionsCount() const
{
	return m_expressions.size();
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_ITEM_IMPL_HPP__
