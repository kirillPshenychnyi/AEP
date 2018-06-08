#include "stdafx.h"

#include "aep\api\aep_iaccessor.hpp"

#include "aep\checkers\aep_base_checker.hpp"
#include "aep\utils\aep_utils_expression_query.hpp"
#include "aep\checkers\resources\aep_checker_resources.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"
#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_process_cast.hpp"
#include "vlog_data_model\api\vlog_dm_design_unit.hpp"
#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"

#include "aep_model\api\aep_model_iaccessor.hpp"
#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_builder.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

BaseAepChecker::BaseAepChecker( IAccessor & _accessor )
	:	m_accessor( _accessor )
	,	m_currentUnit( nullptr )
	,	m_currentSuspectNumber( 1 )
{
}

/***************************************************************************/

std::string
BaseAepChecker::regenerateExpression( VlogDM::Expression const & _expression ) const
{
	return m_accessor.getVlogDm().regenerateExpression( _expression );
}

/***************************************************************************/

int 
BaseAepChecker::calculateBitwidth( VlogDM::Expression const & _expression )
{
	return m_accessor.getVlogDm().calculateBitwidth( _expression );
}

/***************************************************************************/

int 
BaseAepChecker::calculateBitwidth( VlogDM::BaseIdentifier const & _id )
{
	return m_accessor.getVlogDm().calculateBitwidth( _id );
}

/***************************************************************************/

AepModel::AssertionContext & 
BaseAepChecker::retrieveAssertionContext()
{
	using namespace AepModel;

	AepModel::IAccessor & aepAccessor = m_accessor.getAepModel();

	auto context
		= aepAccessor.takeAssertionContext( m_currentUnit->getName() );

	return 
		context
		?	*context
		:	aepAccessor.addContext( m_currentUnit->getName() );
}

/***************************************************************************/

void 
BaseAepChecker::setControls( AepModel::OvlCheckerBuilder & _builder ) const
{
	auto const & clock = m_accessor.getClockParams();

	_builder.setClock( clock.first );
	_builder.setClockEdge( clock.second );

	auto reset = m_accessor.getResetParams();
	
	_builder.setReset( reset ? reset->first : Resources::CommonValues::Reset );
	_builder.setResetPolarity( reset ? reset->second : AepModel::ResetPolarity::Kind::Default );

	_builder.setEnable( Resources::CommonValues::Enable );
}

/***************************************************************************/

void
BaseAepChecker::addInputPorts( 
		VlogDM::Expression const & _expression
	,	AepModel::AssertionContext & _context 
)
{
	Utils::ExpressionQuery< VlogDM::PrimaryIdentifier > idsQuery(
		[ & ]( VlogDM::PrimaryIdentifier const & _id )
		{
			_context.addInputPort( 
					_id.getIdentifier().getName()
				,	_id.getIdentifier().getName()
				,	calculateBitwidth( _id.getIdentifier() )
			);
		}
	);

	idsQuery.query( _expression );
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
			m_currentUnit = &_unit;

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