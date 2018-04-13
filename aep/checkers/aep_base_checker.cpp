#include "stdafx.h"

#include "aep\checkers\aep_base_checker.hpp"
#include "aep\api\aep_iaccessor.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"
#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_process_cast.hpp"

#include "vlog_data_model\api\vlog_dm_design_unit.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

BaseAepChecker::BaseAepChecker( IAccessor & _accessor )
	:	m_accessor( _accessor )
{
}

/***************************************************************************/

template< typename _ProcessKind >
void 
BaseAepChecker::browseProcesses( ProcessCallback< _ProcessKind > _callBack )
{
	using namespace VlogDM;

	ProcessCast< _ProcessKind > processCast;

	m_accessor.getVlogDm().forEachDesignUnit(
		[ & ]( DesignUnit const & _unit )
		{
			const int nProcesses = _unit.getProcessesCount();

			for( int i = 0; i < nProcesses; ++i )
			{
				Process const & process = _unit.getProcess( i );

				if( auto castRes = processCast.cast( process ) )
					_callBack( *castRes );
			}
		}
	);
}

/***************************************************************************/

template
void
BaseAepChecker::browseProcesses< VlogDM::ContinuousAssignment >(
	ProcessCallback< VlogDM::ContinuousAssignment > 
);

template
void
BaseAepChecker::browseProcesses< VlogDM::BehavioralProcess >( 
	ProcessCallback< VlogDM::BehavioralProcess > 
);

/***************************************************************************/

}