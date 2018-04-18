#include "stdafx.h"

#include "vlog_import_expression_bitwidth_engine_fixture.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"

#include "vlog_data_model\api\vlog_dm_process_cast.hpp"
#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"
#include "vlog_data_model\api\vlog_dm_statement_cast.hpp"
#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"

#include "vlog_data_model\api\vlog_dm_design_unit.hpp"

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

void
ExpressionBitwidthEngineFixture::expectBitwidth( 
		VlogDM::Expression const & _expression
	,	int _expectedWidth 
)
{
	int actualWidth = getVlogDm().calculateBitwidth( _expression );

	REQUIRE( actualWidth == _expectedWidth );
}

/***************************************************************************/

VlogDM::ContinuousAssignment const & 
ExpressionBitwidthEngineFixture::getContiniousAssignment( 
		std::string const & _unit
	,	int _idx 
)
{
	return getProcess< VlogDM::ContinuousAssignment >( _unit, _idx );
}

/***************************************************************************/

VlogDM::BehavioralProcess const &
ExpressionBitwidthEngineFixture::getSequentialProcess( 
		std::string const & _unit
	,	int _idx 
)
{
	return getProcess< VlogDM::BehavioralProcess >( _unit, _idx );
}

/***************************************************************************/

VlogDM::BlockingAssignment const & 
ExpressionBitwidthEngineFixture::getBlockingAssign( 
		std::string const & _unit
	,	int _idx 
)
{
	using namespace VlogDM;

	BehavioralProcess const & process = getSequentialProcess( _unit, _idx );

	return checkCast< Statement, BlockingAssignment, StatementCast >( process.getStatement() );
}

/***************************************************************************/

template< typename _TProcess >
_TProcess const & 
ExpressionBitwidthEngineFixture::getProcess( std::string const & _unitName, int _idx )
{
	auto unit = getVlogDm().findUnit( _unitName );

	REQUIRE( unit.is_initialized() );

	REQUIRE( _idx < unit->getProcessesCount() );

	return 
		checkCast< VlogDM::Process, _TProcess, VlogDM::ProcessCast >( unit->getProcess( _idx ) );
}

/***************************************************************************/

}