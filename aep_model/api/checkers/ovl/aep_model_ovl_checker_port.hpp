#ifndef __AEP_MODEL_OVL_CHECKER_PORT_HPP__
#define __AEP_MODEL_OVL_CHECKER_PORT_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\checker_values\aep_model_port_kind.hpp"

#include <boost\functional\hash.hpp>
#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct OvlCheckerPort
	:	public boost::noncopyable
{

/***************************************************************************/

	typedef
		std::unique_ptr< OvlCheckerPort >
		Ptr;

/***************************************************************************/

	virtual ~OvlCheckerPort() = default;

	virtual OvlCheckerPortKind::Kind getKind() const = 0;

	virtual std::string kindToString() const = 0;

	virtual std::string const & getValue() const = 0;

	virtual bool isRedefined() const = 0;

	virtual void setValue( std::string const & _value ) = 0;

/***************************************************************************/

};

/***************************************************************************/


struct CheckerPortHasher
{

/***************************************************************************/

	std::size_t operator() ( OvlCheckerPort::Ptr const & _port ) const
	{
		return boost::hash_value( _port->getKind() );
	}

	std::size_t operator() ( OvlCheckerPortKind::Kind _type ) const
	{
		return boost::hash_value( _type );
	}

/***************************************************************************/

};

/***************************************************************************/

struct CheckerPortComparator
{

/***************************************************************************/

	bool operator () (
			OvlCheckerPort::Ptr const & _first
		,	OvlCheckerPort::Ptr const & _second
	) const
	{
		return _first->getKind() == _second->getKind();
	}

	bool operator () (
			OvlCheckerPort::Ptr const & _first
		,	OvlCheckerPortKind::Kind _second
	) const
	{
		return _first->getKind() == _second;
	}

	bool operator () (
			OvlCheckerPortKind::Kind _first
		,	OvlCheckerPort::Ptr const & _second
	) const
	{
		return _first == _second->getKind();
	}

/***************************************************************************/

};

/***************************************************************************/

}

#endif //!__AEP_MODEL_OVL_CHECKER_PORT_HPP__