#ifndef __AEP_MODEL_BASE_CHECKER_IMPL_HPP__
#define __AEP_MODEL_BASE_CHECKER_IMPL_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"

#include "aep_model\api\checkers\ovl\aep_model_ovl_generic_parameter.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_port.hpp"

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"

#include <boost\unordered_set.hpp>
#include <vector>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

class OvlCheckerImpl
	:	public OvlChecker
{

/***************************************************************************/

	typedef
		boost::unordered_set<
				OVlCheckerGenericParameter::Ptr
			,	GenericParamHasher
			,	GenericParamComparator
		>
		GenericSet;

	typedef
		boost::unordered_set<
			OvlCheckerPort::Ptr
		,	CheckerPortHasher
		,	CheckerPortComparator
		>
		PortsSet;

	/*typedef
		Containers::Vector< CheckerDeclaredWire >
		WiresList;*/

/***************************************************************************/

public:

/***************************************************************************/

	OvlCheckerImpl(
			OvlCheckerIds::Kind _id
		,	std::string const & _instanceName
		,	std::string const &	_moduleFileName
		,	int _suspectLine
	);

/***************************************************************************/

	OvlCheckerIds::Kind getId() const final;

	boost::optional < OVlCheckerGenericParameter & > getParameter(
			GenericType::Kind _type
	) const final;

	void addParameter( std::unique_ptr< OVlCheckerGenericParameter > _parameter  );

	void setPort(
			OvlCheckerPortKind::Kind _type
		,	std::string const & _value
	) final;

	boost::optional < OvlCheckerPort & > getPort(
		OvlCheckerPortKind::Kind _type
	) const final;

	/*void setPortAsWire(
			OvlCheckerPortKind::Kind _type
		,	std::string const & _lhs
		,	std::string const & _rhs
		,	int _width
	) final;*/

	void addPort( std::unique_ptr< OvlCheckerPort > _port );

	void foreachGeneric( GenericParameterCallback const & _functor ) const final;

	//void foreachPort( ForEachPort const & _functor ) const final;

	//void foreachWire( ForEachWire const & _functor ) const final;

	//OvlGenericIteratorPtr browseGenerics () const final;

	//PortIteratorPtr browsePorts() const final;

	//OvlChecker::WireIteratorPtr browseWiresToDeclare() const final;

	int getWiresCount() const final;

	int getGenericsCount () const final;

	int getPortsCount () const final;

	std::string const & getModuleFileName() const final;

	int getSuspectCodeLine() const final;

	std::string const & getInstanceName() const final;

/***************************************************************************/

private:

/***************************************************************************/

	GenericSet m_generics;

	PortsSet m_ports;

	//WiresList m_wires;

	std::string const m_instanceName;

	std::string const m_moduleFileName;

	const int m_suspectLine;

	const OvlCheckerIds::Kind m_id;

/***************************************************************************/

};

/***************************************************************************/

inline
OvlCheckerIds::Kind 
OvlCheckerImpl::getId() const
{
	return m_id;
}

/***************************************************************************/

inline
int 
OvlCheckerImpl::getWiresCount() const
{
	return 0;
}

/***************************************************************************/

inline
int 
OvlCheckerImpl::getGenericsCount() const
{
	return m_generics.size();
}

/***************************************************************************/

inline
int 
OvlCheckerImpl::getPortsCount() const
{
	return 0;
}

/***************************************************************************/

inline
std::string const & 
OvlCheckerImpl::getModuleFileName() const
{
	return m_moduleFileName;
}

/***************************************************************************/

inline
int 
OvlCheckerImpl::getSuspectCodeLine() const
{
	return m_suspectLine;
}

/***************************************************************************/

inline
std::string const & 
OvlCheckerImpl::getInstanceName() const
{
	return m_instanceName;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_BASE_CHECKER_IMPL_HPP__
