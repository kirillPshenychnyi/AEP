#ifndef __AEP_MODEL_IACCESSOR_HPP__
#define __AEP_MODEL_IACCESSOR_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_iaccessor.hpp"

#include "aep_model\api\contexsts\aep_model_assertion_contexts_set.hpp"
#include "aep_model\api\checkers\aep_model_ovl_checkers_factory.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct Accessor
	:	public IAccessor
{

/***************************************************************************/

public:

/***************************************************************************/

	Accessor();

	OvlCheckersFactory const& getCheckersFactory() const final;

	boost::optional< AssertionContext & > takeAssertionContext( 
		std::string const & _dutName 
	) final;
 
	AssertionContext & addContext( std::string const & _dutName ) final;

	void forEachContext( AssertionContextCallback _callback );

	void forEachContext( ConstAssertionContextCallback _callback ) const;

	void regenerateAssertions( std::string const & _path ) const; 

/***************************************************************************/

private:

/***************************************************************************/

	std::unique_ptr< OvlCheckersFactory > m_checkersFactory;

	std::unique_ptr< AssertionContextSet > m_contextSet;

/***************************************************************************/

};

/***************************************************************************/

inline
OvlCheckersFactory const& 
Accessor::getCheckersFactory() const
{
	assert( m_checkersFactory );

	return *m_checkersFactory;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_IACCESSOR_HPP__
