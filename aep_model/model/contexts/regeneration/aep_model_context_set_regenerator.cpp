#include "stdafx.h"

#include "aep_model\model\contexts\regeneration\aep_model_context_set_regenerator.hpp"

#include "aep_model\api\contexsts\aep_model_assertion_contexts_set.hpp"
#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_generic_parameter.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_port.hpp"

#include "aep_model\model\aep_model_resources.hpp"

#include "common_tools\utils\string_utils.hpp"

#include <functional>

/***************************************************************************/

namespace AepModel { 

/***************************************************************************/

ContextSetRegenerator::ContextSetRegenerator( 
		AssertionContextSet const & _contextSet
	,	std::ostream & _stream 
	)
	:	m_contextSet( _contextSet )
	,	m_targetStream( _stream )
{
}

/***************************************************************************/

void 
ContextSetRegenerator::run()
{
	m_targetStream 
		<< Resources::Strings::Header
		<< std::endl;
	
	m_contextSet.forEachConstAssertionContext(
		[ & ]( AssertionContext const & _context )
		{
			_context.forEachInstance(
				std::bind( 
						&ContextSetRegenerator::regenerateContext
					,	this
					,	std::placeholders::_1
					,	std::ref( _context )
				)
			);
		}
	);

	m_targetStream << std::endl;

	regenerateTopLevel();
}

/***************************************************************************/

void 
ContextSetRegenerator::regenerateContext( 
		std::string const & _instanceName
	,	AssertionContext const & _context 
)
{
	m_targetStream << std::endl;

	std::string moduleName{ 
		Tools::fillTemplate( 
				Resources::Strings::AepModuleName
			,	_context.getDUTName() 
			,	_instanceName 
		) 
	};

	m_targetStream 
		<<	Tools::fillTemplate( 
					Resources::HdlPatterns::ModuleDeclaration
				,	moduleName
			);

	regeneratePorts( _context );

	regenerateCheckers( _context );

	m_targetStream 
		<<	std::endl
		<<	Tools::fillTemplate( 
					Resources::HdlPatterns::Endmodule
				,	moduleName
			)
		<<	std::endl;
}

/***************************************************************************/

void 
ContextSetRegenerator::regeneratePorts( AssertionContext const & _context )
{
	const int nInputs = _context.getInputsCount();
	int regenerated = 0;
	
	m_targetStream << Resources::Separators::OpenParentheses;

	_context.forEachInputPort(
		[ & ]( AssertionContext::PortInfo const & _info )
		{
			m_targetStream << _info.m_portName;

			if( regenerated != nInputs - 1 )
				m_targetStream << Resources::Separators::Coma;
			
			++regenerated;
		}
	);

	m_targetStream
		<< Resources::Separators::CloseParentheses
		<< Resources::Separators::Semicolon
		<< std::endl;

	_context.forEachInputPort(
		[ & ]( AssertionContext::PortInfo const & _info )
		{
			regeneratSignal(
					Resources::HdlPatterns::WireDeclaration
				,	Resources::HdlPatterns::VectorDeclaration
				,	_info.m_width
				,	_info.m_portName
			);
		}
	);
}

/***************************************************************************/

void 
ContextSetRegenerator::regenerateCheckers( AssertionContext const & _context )
{
	_context.forEachChecker(
		std::bind( 
				&ContextSetRegenerator::regenerateChecker
			,	this
			,	std::placeholders::_1 
		)
	);
}

/***************************************************************************/

void 
ContextSetRegenerator::regenerateChecker( OvlChecker const & _checker )
{
	_checker.foreachInnerWire(
		[ & ]( OvlChecker::InnerWireInfo const & _wireInfo )
		{		
			regeneratSignal(
					Resources::HdlPatterns::AssignedWireDeclaration
				,	Resources::HdlPatterns::AssignedVectorDeclaration
				,	_wireInfo.m_width
				,	_wireInfo.m_lhs
				,	_wireInfo.m_rhs
			);
		}
	);

	m_targetStream 
		<<	std::endl
		<<	Resources::Separators::Tab
		<<	OvlCheckerIds::toString( _checker.getId() );

	m_targetStream 
		<<	'#'
		<<	Resources::Separators::OpenParentheses;

	int regenerated = 0;
	const int nGenerics = _checker.getGenericsCount();
	_checker.foreachGeneric(
		[ & ]( OvlCheckerGenericParameter const & _generic )
		{
			regenerateAssignmentParam< OvlCheckerGenericParameter >( 
					nGenerics
				,	regenerated 
				,	_generic
				,	std::bind( &OvlCheckerGenericParameter::kindToString, std::placeholders::_1 )
				,	std::bind( &OvlCheckerGenericParameter::valueToString, std::placeholders::_1 )
			);
		}
	);

	m_targetStream 
		<< std::endl 
		<< Resources::Separators::Tab
		<< Resources::Separators::CloseParentheses
		<< std::endl;

	m_targetStream << Resources::Separators::Tab << _checker.getInstanceName();

	m_targetStream << Resources::Separators::Tab << Resources::Separators::OpenParentheses;
	
	regenerated = 0;
	const int nPorts = _checker.getPortsCount();
	_checker.foreachPort(
		[ & ]( OvlCheckerPort const & _port )
		{
			regenerateAssignmentParam< OvlCheckerPort >( 
					nPorts
				,	regenerated 
				,	_port
				,	std::bind( &OvlCheckerPort::kindToString, std::placeholders::_1 )
				,	std::bind( &OvlCheckerPort::getValue, std::placeholders::_1 )
			);
		}
	);

	m_targetStream
		<< std::endl
		<< Resources::Separators::Tab
		<< Resources::Separators::CloseParentheses
		<< Resources::Separators::Semicolon
		<< std::endl;
}

/***************************************************************************/

void 
ContextSetRegenerator::regenerateInstances( AssertionContext const & _context )
{
	_context.forEachInstance(
		std::bind( 
				&ContextSetRegenerator::regenerateInstance
			,	this
			,	std::ref( _context )
			,	std::placeholders::_1 
		)
	);
}

/***************************************************************************/

void 
ContextSetRegenerator::regenerateInstance( 
		AssertionContext const & _context
	,	std::string const & _instance 
)
{
	std::string moduleName{ 
		Tools::fillTemplate( 
				Resources::Strings::AepModuleName
			,	_context.getDUTName()
			,	_instance
		) 
	};

	m_targetStream 
		<< Resources::Separators::Tab
		<<	Tools::fillTemplate( 
					Resources::HdlPatterns::BeginInstantiation
				,	moduleName
				,	moduleName
			);

	int nPorts = _context.getInputsCount();
	int regenerated = 0;
	_context.forEachInputPort(
		[ & ]( AssertionContext::PortInfo const & _info )
		{
			regenerateAssignmentParam< AssertionContext::PortInfo >(
					nPorts
				,	regenerated
				,	_info
				,	[]( AssertionContext::PortInfo const & _item ){ return _item.m_portName; }
				,	[ & ]( AssertionContext::PortInfo const & _item )
					{ 
						return Tools::fillTemplate( 
										Resources::HdlPatterns::InnerSignalRefererence
									,	_instance
									,	_item.m_portValue
								);
					}
			);
		}
	);

	m_targetStream
		<< std::endl
		<< Resources::Separators::Tab
		<< Resources::Separators::CloseParentheses
		<< Resources::Separators::Semicolon
		<< std::endl;
}

/***************************************************************************/

void 
ContextSetRegenerator::regenerateTopLevel()
{
	m_targetStream 
		<<	Tools::fillTemplate( 
					Resources::HdlPatterns::ModuleDeclaration
				,	Resources::Strings::TopAepModuleName
			);

	m_targetStream
		<< Resources::Separators::OpenParentheses
		<< Resources::Separators::CloseParentheses
		<< Resources::Separators::Semicolon
		<< std::endl;

	m_contextSet.forEachConstAssertionContext(
		std::bind(	
				&ContextSetRegenerator::regenerateInstances
			,	this
			,	std::placeholders::_1
		)
	);

	m_targetStream 
		<< std::endl
		<< Tools::fillTemplate( 
				Resources::HdlPatterns::Endmodule
			,	Resources::Strings::TopAepModuleName 
		);
}

/***************************************************************************/

template< typename _ParamKind >
void
ContextSetRegenerator::regenerateAssignmentParam(
		int _nTotal
	,	int & _currentItem
	,	_ParamKind const & _item
	,	std::function< std::string ( _ParamKind const& ) > _nameGetter
	,	std::function< std::string ( _ParamKind const& ) > _valueGetter
)
{
	m_targetStream 
		<< std::endl << Resources::Separators::Tab << Resources::Separators::Tab;

	m_targetStream
		<<	Tools::fillTemplate( 
					Resources::HdlPatterns::AssignmentPattern
				,	_nameGetter( _item )
				,	_valueGetter( _item )
			);

	if( _currentItem != _nTotal - 1 )
		m_targetStream << Resources::Separators::Coma;
			
	++_currentItem;
}

/***************************************************************************/

template< typename ..._Args >
void 
AepModel::ContextSetRegenerator::regeneratSignal(
		std::string const & _scalarPattern
	,	std::string const & _vectorPattern
	,	int _width
	,	_Args... _params
)
{
	m_targetStream << std::endl << std::endl << Resources::Separators::Tab;

	if( _width == 1 )
		m_targetStream << Tools::fillTemplate( _scalarPattern, _params... );
	else
	{
		m_targetStream 
			<<	Tools::fillTemplate( _vectorPattern, _width - 1, 0, _params... );
	}
}

/***************************************************************************/

}