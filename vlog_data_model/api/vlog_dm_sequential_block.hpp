#ifndef __VLOG_DM_SEQUENTIAL_BLOCK_HPP__
#define __VLOG_DM_SEQUENTIAL_BLOCK_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_statement.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct SequentialBlock
	:	public Statement
{

/***************************************************************************/

	virtual Statement const & getStatement( int _idx ) const = 0;

	virtual int getStatementsCount() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_SEQUENTIAL_BLOCK_HPP__
