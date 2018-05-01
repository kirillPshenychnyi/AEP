#ifndef __AEP_MODEL_OVL_CHECKER_PORT_IMPL_HPP__
#define __AEP_MODEL_OVL_CHECKER_PORT_IMPL_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_port.hpp"

namespace AepModel {

/***************************************************************************/

class OvlCheckerPortImpl
	:	public OvlCheckerPort
{

/***************************************************************************/

public:

/***************************************************************************/

	OvlCheckerPortImpl( OvlCheckerPortKind::Kind _kind );

/***************************************************************************/

public:

/***************************************************************************/

	OvlCheckerPortKind::Kind getKind() const final;
	
	std::string kindToString() const final;
	
	std::string const & getValue() const final;

	bool isRedefined() const final;
	 
	void setValue( std::string const & _value ) final;

/***************************************************************************/

private:

/***************************************************************************/

	std::string m_value;

	OvlCheckerPortKind::Kind m_kind;

/***************************************************************************/

};

/***************************************************************************/

OvlCheckerPortImpl::OvlCheckerPortImpl( OvlCheckerPortKind::Kind _kind )
	:	m_kind( _kind )
{
}

/***************************************************************************/

inline
OvlCheckerPortKind::Kind OvlCheckerPortImpl::getKind() const
{
	return m_kind;
}

/***************************************************************************/

inline 
std::string 
OvlCheckerPortImpl::kindToString() const
{
	return OvlCheckerPortKind::toString( m_kind );
}

/***************************************************************************/

inline 
std::string const & 
OvlCheckerPortImpl::getValue() const
{
	return m_value;
}

/***************************************************************************/

inline 
bool 
OvlCheckerPortImpl::isRedefined() const
{
	return false;
}

/***************************************************************************/

inline 
void 
OvlCheckerPortImpl::setValue( std::string const & _value )
{
	m_value = _value;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_PORT_IMPL_HPP__
