#ifndef __AEP_BASE_CHECKER_HPP__
#define __AEP_BASE_CHECKER_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "aep_model\api\aep_model_fwd.hpp"

#include <boost\noncopyable.hpp>
#include <functional>

/***************************************************************************/

namespace Aep {

/***************************************************************************/

struct IAccessor;

/***************************************************************************/

class BaseAepChecker
	:	public boost::noncopyable
{

/***************************************************************************/

	template< typename _TProcess >
	using ProcessCallback = std::function< void( _TProcess const & ) >;

/***************************************************************************/

protected:

/***************************************************************************/

	BaseAepChecker( IAccessor & _accessor );

/***************************************************************************/

	template< typename _ProcessKind >
	void browseProcesses( ProcessCallback< _ProcessKind > _callback );
	
	virtual void analyze() = 0;

	std::string regenerateExpression( VlogDM::Expression const & _expression ) const;

	int calculateBitwidth( VlogDM::Expression const & _expression );

	AepModel::AssertionContext & retrieveAssertionContext();

/***************************************************************************/

protected:

/***************************************************************************/

	IAccessor & m_accessor;

	const VlogDM::DesignUnit * m_currentUnit;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_BASE_CHECKER_HPP__
