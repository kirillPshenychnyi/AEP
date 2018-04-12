#ifndef __AEP_MODEL_IACCESSOR_HPP__
#define __AEP_MODEL_IACCESSOR_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_iaccessor.hpp"

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

/***************************************************************************/

private:

/***************************************************************************/

	std::unique_ptr< OvlCheckersFactory > m_checkersFactory;

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
