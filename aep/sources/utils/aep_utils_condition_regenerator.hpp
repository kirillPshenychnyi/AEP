#ifndef __AEP_UTILS_CONDITION_REGENERATOR_HPP__
#define __AEP_UTILS_CONDITION_REGENERATOR_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"

/***************************************************************************/

namespace Aep {
namespace Utils {

/***************************************************************************/

class ConditionRegenerator
	:	public VlogDM::StatementDefaultVisitor
{

/***************************************************************************/

public:

/***************************************************************************/

	ConditionRegenerator( 
			VlogDM::IAccessor const & _vlogDm
		,	VlogDM::Statement const & _stmt 
		,	int _branch 
	);

	void run();

	std::string const & getResult() const;

	void forEachExpression( 
		std::function< void( VlogDM::Expression const & ) > _callback
	) const;

/***************************************************************************/

private:

/***************************************************************************/

	void visit( VlogDM::ConditionalStatement const & _cond ) final;

	void visit( VlogDM::CaseStatement const & _case ) final;

/***************************************************************************/

	template< typename _TStmt >
	void createInvertedCondition( 
			_TStmt const & _stmt
		,	int _nBranches
		,	std::function< VlogDM::Expression const &( int ) > _conditionGetter
		,	std::function< std::string( VlogDM::Expression const & ) > _conditionRegenerator
	);

/***************************************************************************/

private:

/***************************************************************************/

	std::vector< const VlogDM::Expression * > m_collected;
	
	VlogDM::IAccessor const & m_vlogDm;
	
	VlogDM::Statement const & m_stmt; 
	
	std::string m_result;

	int m_branchIdx;

/***************************************************************************/

};

/***************************************************************************/

inline
std::string const & 
ConditionRegenerator::getResult() const
{
	return m_result;
}

/***************************************************************************/

inline 
void 
ConditionRegenerator::forEachExpression( 
	std::function< void ( VlogDM::Expression const& ) > _callback
) const
{
	for( auto expression : m_collected )
		_callback( *expression );
}

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__AEP_UTILS_CONDITION_REGENERATOR_HPP__
