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

	~Accessor() = default;
	
	void runEngine( 
			GlobalClockParameters const & _clock
		,	boost::optional< GlobalResetParameters const & > _reset
	) final;

	VlogDM::IAccessor const & getVlogDm() const final;
	
	AepModel::IAccessor & getAepModel() final;

	GlobalClockParameters const & getClockParams() const final;

	boost::optional< GlobalResetParameters const & > getResetParams() const final;

/***************************************************************************/

private:

/***************************************************************************/

	void addContolPorts();

	void addInstancesToContexts();

	void addInstancesToContext( AepModel::AssertionContext & _context );

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::IAccessor const & m_vlogDm;

	AepModel::IAccessor & m_aepModel;

	GlobalClockParameters m_clockParams;

	boost::optional< GlobalResetParameters > m_resetParams;

/***************************************************************************/

};

/***************************************************************************/

inline
VlogDM::IAccessor const & 
Accessor::getVlogDm() const
{
	return m_vlogDm;
}

/***************************************************************************/

inline 
AepModel::IAccessor & 
Accessor::getAepModel()
{
	return m_aepModel;
}

/***************************************************************************/

inline
IAccessor::GlobalClockParameters const & 
Accessor::getClockParams() const
{
	return m_clockParams;
}

/***************************************************************************/

inline 
boost::optional< IAccessor::GlobalResetParameters const& >
Accessor::getResetParams() const
{
	return 
		m_resetParams 
		?	*m_resetParams
		:	boost::optional< GlobalResetParameters const& >();
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_ACCESSOR_HPP__
