#ifndef __VLOG_DM_CASE_STATEMENT_IMPL_HPP__
#define __VLOG_DM_CASE_STATEMENT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_conditional_statement.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_base_case_item.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <vector>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class CaseStatementImpl
	:	public LocatedImpl< Writable::CaseStatement >
{

/***************************************************************************/

	typedef
		LocatedImpl< Writable::CaseStatement >
		BaseClass;

	typedef
		std::vector< BaseCaseItemPtr >
		CaseItems;

/***************************************************************************/

public:

/***************************************************************************/

	CaseStatementImpl( 
			Location const & _location
		,	ExpressionPtr _caseExpression
		,	CaseKind::Kind _kind
		,	bool _isParallelCase
		,	bool _isFullCase
	);

/***************************************************************************/

	Expression const & getCaseExpression() const final;

	int getItemsCount() const final;

	BaseCaseItem const & getItem( int _idx ) const final;

	void accept( StatementVisitor & _visitor ) const final;

	void addBranch( BaseCaseItemPtr _item ) final;

	bool isParallelCase() const override;

	bool isFullCase() const override;
	
	CaseKind::Kind getCaseKind() const override;

/***************************************************************************/

private:

/***************************************************************************/

	CaseItems m_items;

	ExpressionPtr m_caseExpression;

	const CaseKind::Kind m_kind;

	bool m_isParallelCase;
	bool m_isFullCase;

/***************************************************************************/

};

/***************************************************************************/

CaseStatementImpl::CaseStatementImpl(
		Location const & _location
	,	ExpressionPtr _caseExpression 
	,	CaseKind::Kind _kind
	,	bool _isParallelCase
	,	bool _isFullCase
	)
	:	BaseClass( _location )
	,	m_caseExpression( std::move( _caseExpression ) )
	,	m_kind( _kind )
	,	m_isParallelCase( _isParallelCase )
	,	m_isFullCase( _isFullCase )
{
}

/***************************************************************************/

inline 
Expression const & 
CaseStatementImpl::getCaseExpression() const
{
	assert( m_caseExpression );

	return *m_caseExpression;
}

/***************************************************************************/

inline 
int 
CaseStatementImpl::getItemsCount() const
{
	return m_items.size();
}

/***************************************************************************/

inline 
BaseCaseItem const & 
CaseStatementImpl::getItem( int _idx ) const
{
	return *m_items[ _idx ];
}

/***************************************************************************/

inline
void 
CaseStatementImpl::accept( StatementVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

inline 
void 
CaseStatementImpl::addBranch( BaseCaseItemPtr _item )
{
	m_items.push_back( std::move( _item ) );
}

/***************************************************************************/

inline 
bool 
CaseStatementImpl::isParallelCase() const
{
	return m_isParallelCase;
}

/***************************************************************************/

inline 
bool 
CaseStatementImpl::isFullCase() const
{
	return m_isFullCase;
}

inline
CaseKind::Kind 
CaseStatementImpl::getCaseKind() const
{
	return m_kind;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_STATEMENT_IMPL_HPP__
