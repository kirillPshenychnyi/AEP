#ifndef __VLOG_DM_BLOCKING_ASSIGNMENT_IMPL_HPP__
#define __VLOG_DM_BLOCKING_ASSIGNMENT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class BlockingAssignmentImpl
	:	public LocatedImpl< BlockingAssignment >
{

/***************************************************************************/

	typedef
		std::unique_ptr< BinaryOperator >
		BinaryOperatorPtr;

	typedef
		LocatedImpl< BlockingAssignment >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	BlockingAssignmentImpl( 
			Location const & _location 
		,	BinaryOperatorPtr _assignment
	);

/***************************************************************************/

	void accept( StatementVisitor & _visitor ) const override;

	BinaryOperator const & getAssignment() const override;

/***************************************************************************/

private:

/***************************************************************************/

	BinaryOperatorPtr m_binaryOperator;

/***************************************************************************/

};

/***************************************************************************/

BlockingAssignmentImpl::BlockingAssignmentImpl( 
		Location const & _location 
	,	BinaryOperatorPtr _assignment
	)
	:	BaseClass( _location )
	,	m_binaryOperator( std::move( _assignment ) )
{}

/***************************************************************************/

void 
BlockingAssignmentImpl::accept( StatementVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

BinaryOperator const & 
BlockingAssignmentImpl::getAssignment() const
{
	return *m_binaryOperator;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_BLOCKING_ASSIGNMENT_IMPL_HPP__
