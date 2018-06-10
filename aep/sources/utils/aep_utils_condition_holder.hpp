#ifndef __AEP_UTILS_CONDITION_COLLECTOR_HPP__
#define __AEP_UTILS_CONDITION_COLLECTOR_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <stack>

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

class ConditionHolder
{

/***************************************************************************/
	
	using Condition = std::pair< const VlogDM::Statement *, int >;

/***************************************************************************/

public:

/***************************************************************************/

	void popCondition()
	{
		m_conditions.pop_back();
	}

	void pushCondition( VlogDM::Statement const & _stmt, int _branchIdx )
	{
		m_conditions.emplace_back( &_stmt, _branchIdx );
	}

	bool hasConditions() const
	{
		return !m_conditions.empty();
	}

	void forEachCondition( 
		std::function< void ( VlogDM::Statement const &, int ) > _callback  
	) const 
	{
		for( auto item : m_conditions )
			_callback( *item.first, item.second );
	}

/***************************************************************************/

private:

/***************************************************************************/

	std::vector< Condition > m_conditions;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // __AEP_UTILS_CONDITION_COLLECTOR_HPP__