#ifndef __AEP_ACCESSOR_HPP__
#define __AEP_ACCESSOR_HPP__

/***************************************************************************/

#include "aep\api\aep_iaccessor.hpp"

#include "aep_model\api\aep_model_fwd.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

class Accessor
	:	public IAccessor
{

/***************************************************************************/

public:

/***************************************************************************/

	Accessor( 
			std::shared_ptr< VlogDM::IAccessor > _vlogDm
		,	std::shared_ptr< AepModel::IAccessor > _aepModel
	);

	void runEngine() final;

	VlogDM::IAccessor const & getVlogDm() const final;
	
	AepModel::IAccessor const & getAepModel() const final;

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::IAccessor const & m_vlogDm;

	AepModel::IAccessor const & m_aepModel;

/***************************************************************************/

};

/***************************************************************************/

inline
VlogDM::IAccessor const & 
Accessor::getVlogDm() const
{
	return m_vlogDm;
}

inline 
AepModel::IAccessor const & 
Accessor::getAepModel() const
{
	return m_aepModel;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_ACCESSOR_HPP__
