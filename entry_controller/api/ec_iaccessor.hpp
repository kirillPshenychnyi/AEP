#ifndef __EC_IACCESSOR_HPP__
#define __EC_IACCESSOR_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "aep\api\aep_iaccessor.hpp"

/***************************************************************************/

namespace EntryController {

/***************************************************************************/

struct IAccessor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual void importVerilog( std::string const& _code ) = 0;

	virtual void runAepAnalysis(
			Aep::IAccessor::GlobalClockParameters & _clockParams
		,	boost::optional< Aep::IAccessor::GlobalResetParameters const & > _resetParams
	) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__EC_IACCESSOR_HPP__
