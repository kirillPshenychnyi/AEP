#ifndef __AEP_MODEL_OVL_GENERIC_PARAMETER_HPP__
#define __AEP_MODEL_OVL_GENERIC_PARAMETER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\checker_values\aep_model_generic_type.hpp"

#include <boost\noncopyable.hpp>
#include <boost\functional\hash.hpp>

/***************************************************************************/

namespace AepModel { 

/***************************************************************************/

struct OvlCheckerGenericVisitor;

/***************************************************************************/

struct OVlCheckerGenericParameter
	:	public boost::noncopyable
{

/***************************************************************************/

	typedef
		std::unique_ptr< OVlCheckerGenericParameter >
		Ptr;

/***************************************************************************/

	virtual GenericType::Kind getKind () const = 0;

	virtual std::string kindToString () const = 0;

	virtual std::string valueToString () const = 0;
	
	virtual bool isRedefined() const = 0;

	virtual void accept ( OvlCheckerGenericVisitor & _visitor ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

struct GenericParamHasher
{

/***************************************************************************/

	std::size_t operator() ( OVlCheckerGenericParameter::Ptr const & _param ) const
	{
		return boost::hash_value( _param->getKind() );
	}

	std::size_t operator() ( GenericType::Kind _type ) const
	{
		return boost::hash_value( _type );
	}

/***************************************************************************/

};

/***************************************************************************/

struct GenericParamComparator
{

/***************************************************************************/

	bool operator () (
			OVlCheckerGenericParameter::Ptr const & _first
		,	OVlCheckerGenericParameter::Ptr const & _second
	) const
	{
		return _first->getKind() == _second->getKind();
	}

	bool operator () (
			 OVlCheckerGenericParameter::Ptr const & _first
		,	 GenericType::Kind _second
	) const
	{
		return _first->getKind() == _second;
	}

	bool operator () (
			GenericType::Kind _first
		,	OVlCheckerGenericParameter::Ptr const & _second
	) const
	{
		return _first == _second->getKind();
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_GENERIC_PARAMETER_HPP__
