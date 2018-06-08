#ifndef __AEP_IACCESSOR_HPP__
#define __AEP_IACCESSOR_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "aep_model\api\aep_model_fwd.hpp"
#include "aep\api\aep_checker_ids.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

struct IAccessor
	:	public boost::noncopyable
{

/***************************************************************************/

	typedef 
		std::pair< std::string, AepModel::ResetPolarity::Kind >
		GlobalResetParameters;

	typedef 
		std::pair< std::string, AepModel::ClockEdge::Kind >
		GlobalClockParameters;
	
/***************************************************************************/

	virtual ~IAccessor() = default;

	virtual void runEngine( 
			CheckerIds _checkers
		,	GlobalClockParameters const & _clock
		,	boost::optional< GlobalResetParameters const& > _reset
	) = 0; 

	virtual VlogDM::IAccessor const & getVlogDm() const = 0;

	virtual AepModel::IAccessor & getAepModel() = 0;

	virtual GlobalClockParameters const & getClockParams() const = 0;

	virtual boost::optional< GlobalResetParameters const & > getResetParams() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_IACCESSOR_HPP__
