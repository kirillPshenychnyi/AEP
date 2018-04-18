#ifndef __VLOD_DM_RANGE_BITWIDTH_PROCESSOR_HPP__
#define __VLOD_DM_RANGE_BITWIDTH_PROCESSOR_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\visitors\vlog_dm_range_visitor.hpp"

/***************************************************************************/

namespace VlogDM {
namespace VlogEngines {

/***************************************************************************/

class RangeBitwidthProcessor
	:	public RangeVisitor
{

/***************************************************************************/

public:

/***************************************************************************/

	RangeBitwidthProcessor();

	int calculate( Range const & _range );

/***************************************************************************/

private:

/***************************************************************************/

	void visit( ExpressionRange const & _range ) final;

	void visit( PartSelectRange const & _range ) final;
	
	void visit( MultidimensionalRange const & _range ) final;

/***************************************************************************/

private:

/***************************************************************************/

	int m_result;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOD_DM_RANGE_BITWIDTH_PROCESSOR_HPP__
