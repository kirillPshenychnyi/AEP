#ifndef __VLOG_DM_SENSITIVITY_LIST_IMPL_HPP__
#define __VLOG_DM_SENSITIVITY_LIST_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_sensitivity_list.hpp"

#include <vector>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class SensitivityListImpl
	:	public LocatedImpl< Writable::SensitivityList >
{

/***************************************************************************/

	typedef
		std::vector< ExpressionPtr >
		ExpressionsList;

	typedef
		LocatedImpl< Writable::SensitivityList >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	SensitivityListImpl( Location const & _location );

/***************************************************************************/

	void addExpression( ExpressionPtr _expression ) final;

	int getExpressionsCount() const final;

	Expression const & getExpression( int _idx ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	ExpressionsList m_expressions;

/***************************************************************************/

};

/***************************************************************************/

SensitivityListImpl::SensitivityListImpl( Location const & _location )
	:	BaseClass( _location )
{

}

/***************************************************************************/

void 
SensitivityListImpl::addExpression( ExpressionPtr _expression )
{
	m_expressions.push_back( std::move( _expression ) );
}

/***************************************************************************/

int 
SensitivityListImpl::getExpressionsCount() const
{
	return m_expressions.size();
}

/***************************************************************************/

Expression const & 
SensitivityListImpl::getExpression( int _idx ) const
{
	return *m_expressions.at( _idx );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_SENSITIVITY_LIST_IMPL_HPP__
