#ifndef __AEP_BASE_CHECKER_HPP__
#define __AEP_BASE_CHECKER_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "aep_model\api\aep_model_fwd.hpp"

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

public:

/***************************************************************************/

	virtual void analyze() = 0;

/***************************************************************************/

protected:

/***************************************************************************/

	template< typename _ProcessKind >
	void browseProcesses( ProcessCallback< _ProcessKind > _callback );

	std::string regenerateExpression( VlogDM::Expression const & _expression ) const;

	int calculateBitwidth( VlogDM::Expression const & _expression );

	int calculateBitwidth( VlogDM::BaseIdentifier const & _id );

	AepModel::AssertionContext & retrieveAssertionContext();

	void setControls( AepModel::OvlCheckerBuilder & _builder ) const;

	void addInputPorts( 
			VlogDM::Expression const & _expression
		,	AepModel::AssertionContext & _context 
	);

/***************************************************************************/

protected:

/***************************************************************************/

	IAccessor & m_accessor;

	const VlogDM::DesignUnit * m_currentUnit;

	int m_currentSuspectNumber;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_BASE_CHECKER_HPP__
