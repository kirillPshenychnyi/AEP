#ifndef __VLOG_DM_CONTINUOUS_ASSIGNMENT_IMPL_HPP__
#define __VLOG_DM_CONTINUOUS_ASSIGNMENT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_process_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ContinuousAssignmentImpl
	:	public LocatedImpl< ContinuousAssignment >
{

/***************************************************************************/

	typedef
		LocatedImpl< ContinuousAssignment >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	ContinuousAssignmentImpl(
			Location const & _location
		,	std::unique_ptr< BinaryOperator > _assignment
	);

/***************************************************************************/

	BinaryOperator const & getAssignment() const override;

	void accept( ProcessVisitor & _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	std::unique_ptr< BinaryOperator > m_assignment;

/***************************************************************************/

};

/***************************************************************************/

ContinuousAssignmentImpl::ContinuousAssignmentImpl(
		Location const & _location
	,	std::unique_ptr< BinaryOperator > _assignment
	)
	:	BaseClass( _location )
	,	m_assignment( _assignment.release() )
{
}

/***************************************************************************/

BinaryOperator const & 
ContinuousAssignmentImpl::getAssignment() const
{
	return *m_assignment;
}

/***************************************************************************/

void 
ContinuousAssignmentImpl::accept( ProcessVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CONTINUOUS_ASSIGNMENT_IMPL_HPP__
