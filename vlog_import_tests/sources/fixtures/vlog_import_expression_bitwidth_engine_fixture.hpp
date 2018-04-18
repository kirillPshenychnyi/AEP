#ifndef __VLOG_IMPORT_BITWIDTH_ENGINE_FIXTURE_HPP__
#define __VLOG_IMPORT_BITWIDTH_ENGINE_FIXTURE_HPP__

/***************************************************************************/

#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

class ExpressionBitwidthEngineFixture
	:	public BaseFixture
{

/***************************************************************************/

public:
	
/***************************************************************************/

	void expectBitwidth( 
			VlogDM::Expression const & _expression
		,	int _expectedWidth 
	);

	VlogDM::ContinuousAssignment const & getContiniousAssignment( 
			std::string const & _unit
		,	int _idx 
	);

	VlogDM::BehavioralProcess const & getSequentialProcess( 
			std::string const & _unit
		,	int _idx 
	);

	VlogDM::BlockingAssignment const & getBlockingAssign( 
			std::string const & _unit
		,	int _idx 
	);

/***************************************************************************/

	template< typename _TProcess >
	_TProcess const & getProcess( 
			std::string const & _unit
		,	int _idx 
	);

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_IMPORT_BITWIDTH_ENGINE_FIXTURE_HPP__
