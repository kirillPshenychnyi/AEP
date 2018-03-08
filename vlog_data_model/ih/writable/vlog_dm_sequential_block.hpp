#ifndef __VLOG_DM_WRITABLE_SEQUENTIAL_BLOCK_HPP__
#define __VLOG_DM_WRITABLE_SEQUENTIAL_BLOCK_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_sequential_block.hpp"
#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable { 

/***************************************************************************/

struct SequentialBlock
	:	public VlogDM::SequentialBlock
{

/***************************************************************************/

	virtual void addStatement( VlogDM::StatementPtr _stmt ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_WRITABLE_SEQUENTIAL_BLOCK_HPP__
