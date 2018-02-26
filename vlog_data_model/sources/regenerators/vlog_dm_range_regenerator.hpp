#ifndef __VLOG_DM_RANGE_REGENERATOR_HPP__
#define __VLOG_DM_RANGE_REGENERATOR_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\visitors\vlog_dm_range_visitor.hpp"

#include "vlog_data_model\sources\regenerators\vlog_dm_base_regenerator.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators {

/***************************************************************************/

class RangeRegenerator
	:	public BaseRegenerator
	,	public RangeVisitor
{

/***************************************************************************/

public:

/***************************************************************************/

	RangeRegenerator( std::ostream & _targetStream );

/***************************************************************************/

	void visit( ExpressionRange const & _range ) override;

	void visit( PartSelectRange const & _range ) override;

	void visit( MultidimensionalRange const & _range ) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_RANGE_REGENERATOR_HPP__
