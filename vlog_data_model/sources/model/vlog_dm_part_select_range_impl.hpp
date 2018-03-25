#ifndef __VLOG_DM_PART_SELECT_RANGE_IMPL_HPP__
#define __VLOG_DM_PART_SELECT_RANGE_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_range_visitor.hpp"

#include "vlog_data_model\api\vlog_dm_part_select_range.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class PartSelectRangeImpl
	:	public LocatedImpl< PartSelectRange >
{

/***************************************************************************/

	typedef
		LocatedImpl< PartSelectRange >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	PartSelectRangeImpl(
			Location const& _location
		,	std::unique_ptr< Expression > _leftBound
		,	std::unique_ptr< Expression > _rightBound
	);

/***************************************************************************/

	Expression const & getRightBound() const final;

	Expression const & getLeftBound() const final;

	void accept( RangeVisitor& _visitor ) const final; 

/***************************************************************************/

private:

/***************************************************************************/

	Expression::Ptr m_leftBound;

	Expression::Ptr m_rightBound;

/***************************************************************************/

};

/***************************************************************************/

inline
PartSelectRangeImpl::PartSelectRangeImpl(
		Location const& _location
	,	std::unique_ptr< Expression > _leftBound
	,	std::unique_ptr< Expression > _rightBound
)	:	BaseClass( _location )
	,	m_leftBound( std::move( _leftBound ) )
	,	m_rightBound( std::move( _rightBound ) )
{
}

/***************************************************************************/

inline
void 
PartSelectRangeImpl::accept( RangeVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

inline
Expression const & 
VlogDM::PartSelectRangeImpl::getRightBound() const
{
	return *m_rightBound;
}

/***************************************************************************/

inline 
Expression const & 
VlogDM::PartSelectRangeImpl::getLeftBound() const
{
	return *m_leftBound;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_PART_SELECT_RANGE_IMPL_HPP__
