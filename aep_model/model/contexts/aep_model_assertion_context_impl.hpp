#ifndef __AEP_MODEL_ASSERTION_CONTEXT_IMPL_HPP__
#define __AEP_MODEL_ASSERTION_CONTEXT_IMPL_HPP__

/***************************************************************************/

#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"

#include <vector>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

class AssertionContextImpl
	:	public AssertionContext
{

/***************************************************************************/

	typedef
		std::vector< PortInfo >
		PortInfos;

	typedef
		std::vector< std::string >
		Instances;

	typedef
		std::vector< OvlCheckerPtr >
		Checkers;

/***************************************************************************/

public:

/***************************************************************************/

	AssertionContextImpl( std::string const & _dutName );

	std::string const & getDUTName() const final;

	void addInputPort( 
			std::string const&  _portName 
		,	std::string const& _portValue
		,	int _width 
	) final;

	void addInstanceName( std::string const & _name ) final;
	
	void addChecker( OvlCheckerPtr _checker );

	void forEachInstance( InstanceCallback _callback ) const final;
	
	void forEachInputPort( InputPortCallback _callback ) const final;

	void forEachChecker( CheckerCallback _callback ) const final;

	int getInputsCount() const final;

/***************************************************************************/

	PortInfos m_additioanalInputs;

	Instances m_instances;

	Checkers m_checkers;

	std::string const m_dutName;

/***************************************************************************/

};

/***************************************************************************/

inline
std::string const & 
AssertionContextImpl::getDUTName() const
{
	return m_dutName;
}

/***************************************************************************/

inline
int 
AssertionContextImpl::getInputsCount() const
{
	return m_additioanalInputs.size();
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_ASSERTION_CONTEXT_IMPL_HPP__
