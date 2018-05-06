#ifndef __VLOG_DM_ITEMS_FACTORY_HPP__
#define __VLOG_DM_ITEMS_FACTORY_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM {
namespace Writable{

/***************************************************************************/

struct ItemsFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual ~ItemsFactory() = default;

	virtual DimensionPtr newUnackedDimension( 
			Location const& _location
		,	std::unique_ptr< Range > _range
	) const = 0;

	virtual	DimensionPtr newPackedDimension( 
			Location const& _location
		,	std::unique_ptr< Range > _range
	) const = 0;
	
	virtual RangePtr newPartSelectRange( 
			Location const& _location
		,	ExpressionPtr _lhs
		,	ExpressionPtr _rhs
	) const = 0;

	virtual RangePtr newExpressionRange( ExpressionPtr _expression ) const = 0;

	virtual MultidimensionalRangePtr newMultidimensionalRange( 
			Location const& _location
	) const = 0;

	virtual BaseIdentifierPtr newIdentifier(
			Location const& _location
		,	Declared const & _declared
		,	RangePtr _range = RangePtr()
	) const = 0;

	virtual ContinuousAssignmentPtr newContinuousAssignment(
			Location const& _location
		,	std::unique_ptr< BinaryOperator > _assignment
	) const = 0;

	virtual BehavioralProcessPtr newBehavioralProcess(
			Location const& _location
		,	StatementPtr _statement
		,	VlogDM::SensitivityListPtr _sensitivityList
	) const = 0;

	virtual SensitivityListPtr newSensitivityList( 
		Location const & _location	
	) const = 0;

	virtual CaseItemPtr newCaseItem(
		Location const & _location
	) const = 0;

	virtual DefaultCaseItemPtr newDefaultCaseItem(
		Location const & _location
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_ITEMS_FACTORY_HPP__
