#ifndef __AEP_BASE_CHECKER_HPP__
#define __AEP_BASE_CHECKER_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <boost\noncopyable.hpp>
#include <functional>

/***************************************************************************/

namespace Aep {

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

	BaseAepChecker( VlogDM::IAccessor const & _accessor );

/***************************************************************************/

	template< typename _ProcessKind >
	void browseProcesses( ProcessCallback< _ProcessKind > _callback );
	
	virtual void analyze() = 0;

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::IAccessor const & m_vlogDm;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_BASE_CHECKER_HPP__
