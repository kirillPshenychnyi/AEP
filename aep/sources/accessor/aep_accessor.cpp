#include "stdafx.h"

#include "aep\sources\accessor\aep_accessor.hpp"
#include "aep\checkers\aep_full_case_syn_directive_checker.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"
#include "vlog_data_model\api\vlog_dm_design_unit.hpp"

#include "aep_model\api\aep_model_iaccessor.hpp"
#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

Accessor::Accessor(
		std::shared_ptr< VlogDM::IAccessor > _vlogDm 
	,	std::shared_ptr< AepModel::IAccessor > _aepModel
)
	:	m_vlogDm( *_vlogDm )
	,	m_aepModel( *_aepModel )
	,	m_clockParams( "", AepModel::ClockEdge::Kind::Default )
	,	m_resetParams( boost::none )

{
}

/***************************************************************************/

void
Accessor::runEngine(
		GlobalClockParameters const & _clock
	,	boost::optional< GlobalResetParameters const & > _reset
)
{
	m_clockParams = _clock;

	if( _reset )
		m_resetParams = *_reset;

	FullCaseSynDirectiveChecker c1( *this );

	c1.analyze();

	addInstancesToContexts();
	addContolPorts();
}

/***************************************************************************/

void 
Accessor::addContolPorts()
{
	m_aepModel.forEachContext(
		[ & ]( AepModel::AssertionContext & _context )
		{
			_context.addInputPort( 
					m_clockParams.first
				,	m_clockParams.first
				,	1
			);

			if( m_resetParams )
			{
				_context.addInputPort( 
						m_resetParams->first
					,	m_resetParams->first
					,	1
				);
			}
		}
	);
}

/***************************************************************************/

void
Accessor::addInstancesToContexts()
{
	m_aepModel.forEachContext(
		std::bind( 
				&Accessor::addInstancesToContext
			,	this 
			,	std::placeholders::_1
		)
	);
}

/***************************************************************************/

void 
Accessor::addInstancesToContext( AepModel::AssertionContext & _context )
{
	m_vlogDm.forEachDesignUnit(
		[ & ]( VlogDM::DesignUnit const & _unit )
		{
			_unit.forEachChildInstance( 
					_context.getDUTName()
				,	std::bind( 
							&AepModel::AssertionContext::addInstanceName
						,	&_context
						,	std::placeholders::_1
					)
			);
		}
	);
}

/***************************************************************************/

}