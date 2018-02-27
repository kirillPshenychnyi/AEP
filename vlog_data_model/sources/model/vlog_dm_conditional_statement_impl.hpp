#ifndef __VLOG_DM_CONDITIONAL_STATEMENT_IMPL_HPP__
#define __VLOG_DM_CONDITIONAL_STATEMENT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_conditional_statement.hpp" 
#include "vlog_data_model\api\vlog_dm_conditional_branch.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <vector>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct ConditionalStatementImpl
	:	public LocatedImpl< Writable::ConditionalStatement >
{

/***************************************************************************/

	typedef
		LocatedImpl< Writable::ConditionalStatement >
		BaseClass;

	typedef
		std::vector< ConditionalBranchPtr >
		Branches;

/***************************************************************************/

public:

/***************************************************************************/

	ConditionalStatementImpl( Location const & _location );

/***************************************************************************/

	int getBranchesCount() const override;

	ConditionalBranch const & getBranch( int _idx ) const override;

	void addBranch( ConditionalBranchPtr _branch ) override;

	void accept( StatementVisitor & _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	Branches m_branches;

/***************************************************************************/

};

/***************************************************************************/

ConditionalStatementImpl::ConditionalStatementImpl( Location const & _location )
	:	BaseClass( _location )
{
}

/***************************************************************************/

int 
ConditionalStatementImpl::getBranchesCount() const
{
	return m_branches.size();
}

/***************************************************************************/

ConditionalBranch const & 
ConditionalStatementImpl::getBranch( int _idx ) const
{
	return *m_branches[ _idx ];
}

/***************************************************************************/

void 
ConditionalStatementImpl::addBranch( ConditionalBranchPtr _branch )
{
	m_branches.push_back( std::move( _branch ) );
}

/***************************************************************************/

void 
ConditionalStatementImpl::accept( StatementVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONDITIONAL_STATEMENT_IMPL_HPP__
