#ifndef __EC_ACCESSOR_HPP__
#define __EC_ACCESSOR_HPP__

/***************************************************************************/

#include "entry_controller\api\ec_iaccessor.hpp"

/***************************************************************************/

namespace VlogDM {

struct IAccessor;

}

namespace Aep {

struct IAccessor;

}

/***************************************************************************/

namespace EntryController {

/***************************************************************************/

class Accessor
	:	public IAccessor
{

/***************************************************************************/

public:

/***************************************************************************/

	Accessor(
			const std::shared_ptr< VlogDM::IAccessor > _vlogDm
		,	const std::shared_ptr< Aep::IAccessor > _aepAccessor
	);

/***************************************************************************/

public:

/***************************************************************************/

	void importVerilog( std::string const & _code ) final;

	void runAepAnalysis(
			Aep::IAccessor::GlobalClockParameters & _clockParams
		,	boost::optional< Aep::IAccessor::GlobalResetParameters const & > _resetParams
	) final;

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::IAccessor & m_vlogDm;
	Aep::IAccessor & m_aepAccessor;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__EC_ACCESSOR_HPP__
