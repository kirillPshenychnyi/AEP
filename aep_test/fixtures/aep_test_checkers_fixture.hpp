#ifndef __AEP_TEST_RULES_FIXTURE_HPP__
#define __AEP_TEST_RULES_FIXTURE_HPP__

/***************************************************************************/

#include "aep\api\aep_checker_ids.hpp"
#include "aep\api\aep_iaccessor.hpp"

#include "aep_test\fixtures\aep_test_assertion_context_helper.hpp"

/***************************************************************************/

namespace VlogDM {

	struct IAccessor;
}

namespace AepModel {

	struct IAccessor;
}

namespace EntryController {
	
	struct IAccessor;
}

/***************************************************************************/

namespace AepTest {

/***************************************************************************/

class CheckersFixture
{

/***************************************************************************/

public:

/***************************************************************************/

	CheckersFixture( Aep::CheckerIds _id );

/***************************************************************************/

	void run( 
			std::string const & _code
		,	Aep::IAccessor::GlobalClockParameters const & _clk
		,	boost::optional < Aep::IAccessor::GlobalResetParameters const & > _reset
				=	boost::none
	);

	AssertionContextHelper & expectContext( std::string const & _module );

/***************************************************************************/

private:

/***************************************************************************/

	std::shared_ptr< VlogDM::IAccessor > m_vlogDm;

	std::shared_ptr< Aep::IAccessor > m_aep;

	std::shared_ptr< AepModel::IAccessor > m_aepModel;

	std::shared_ptr< EntryController::IAccessor > m_entryController;

	std::unique_ptr< AssertionContextHelper > m_contextHelper;

	Aep::CheckerIds m_checkerId;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_TEST_RULES_FIXTURE_HPP__
