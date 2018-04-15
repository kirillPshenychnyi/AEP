#ifndef __AEP_MODEL_ASSERTION_CONTEXT_IMPL_HPP__
#define __AEP_MODEL_ASSERTION_CONTEXT_IMPL_HPP__

/***************************************************************************/

#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"

#include <vector>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

class AssertionContextImpl
	:	public AssertionContext
{

/***************************************************************************/

	typedef
		std::vector< std::string >
		Instances;

/***************************************************************************/

public:

/***************************************************************************/

	AssertionContextImpl( std::string const & _dutName );

	std::string const & getDUTName() const final;

	void addInstanceName( std::string const & _name ) final;
	
	void forEachInstance( InstanceCallback _callback ) final;

/***************************************************************************/

	std::string const m_dutName;

	Instances m_instances;

/***************************************************************************/

};

/***************************************************************************/

std::string const & 
AssertionContextImpl::getDUTName() const
{
	return m_dutName;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_ASSERTION_CONTEXT_IMPL_HPP__
