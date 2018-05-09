#ifndef __AEP_MODEL_OVL_GENERIC_PARAMETER_HPP__
#define __AEP_MODEL_OVL_GENERIC_PARAMETER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\checker_values\aep_model_generic_type.hpp"

#include <boost\functional\hash.hpp>

/***************************************************************************/

namespace AepModel { 

/***************************************************************************/

struct OvlCheckerGenericParameterVisitor;
struct OvlCheckerGenericParameterNonConstVisitor;

/***************************************************************************/

struct OvlCheckerGenericParameter
	:	public boost::noncopyable
{

/***************************************************************************/

	typedef
		std::unique_ptr< OvlCheckerGenericParameter >
		Ptr;

/***************************************************************************/

	virtual ~OvlCheckerGenericParameter() = default;

	virtual GenericType::Kind getKind () const = 0;

	virtual std::string kindToString () const = 0;

	virtual std::string valueToString () const = 0;
	
	virtual bool isRedefined() const = 0;

	virtual void accept ( OvlCheckerGenericParameterVisitor & _visitor ) const = 0;

	virtual void accept ( OvlCheckerGenericParameterNonConstVisitor & _visitor ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct GenericParamHasher
{

/***************************************************************************/

	std::size_t operator() ( OvlCheckerGenericParameter::Ptr const & _param ) const
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
			OvlCheckerGenericParameter::Ptr const & _first
		,	OvlCheckerGenericParameter::Ptr const & _second
	) const
	{
		return _first->getKind() == _second->getKind();
	}

	bool operator () (
			 OvlCheckerGenericParameter::Ptr const & _first
		,	 GenericType::Kind _second
	) const
	{
		return _first->getKind() == _second;
	}

	bool operator () (
			GenericType::Kind _first
		,	OvlCheckerGenericParameter::Ptr const & _second
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
