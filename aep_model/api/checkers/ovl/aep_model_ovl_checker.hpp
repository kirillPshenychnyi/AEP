#ifndef __AEP_MODEL_OVL_CHECKER_HPP__
#define __AEP_MODEL_OVL_CHECKER_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker_ids.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_port_kind.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_generic_type.hpp"

#include <functional>

/***************************************************************************/

namespace AepModel
{

/***************************************************************************/

struct OvlCheckerGenericParameter;
struct OvlCheckerPort;

/***************************************************************************/

struct OvlChecker
	:	public boost::noncopyable
{

/***************************************************************************/

	struct InnerWireInfo
	{
		InnerWireInfo( 
				std::string const & _lhs
			,	std::string const & _rhs
			,	int _width
		)
			:	m_lhs( _lhs )
			,	m_rhs( _rhs )
			,	m_width( _width )
		{
		}

		bool operator == ( InnerWireInfo const & _other ) const
		{
			return 
				m_lhs == _other.m_lhs
			&&	m_rhs == _other.m_rhs
			&&	m_width == _other.m_width;
		}

		std::string const m_lhs;
		std::string const m_rhs;
		int m_width; 
	};

	typedef
		std::function< void( OvlCheckerGenericParameter const& ) >
		GenericParameterCallback;

	typedef
		std::function< void( InnerWireInfo const& ) >
		InnerWireCallback;

	typedef
		std::function< void( OvlCheckerPort const& ) >
		PortCallback;

/***************************************************************************/

	virtual ~OvlChecker() = default;

	virtual OvlCheckerIds::Kind getId() const = 0;

	virtual void setPort(
			OvlCheckerPortKind::Kind _type
		,	std::string const & _value
	) = 0;

	virtual std::string const & getModuleFileName() const = 0;

	virtual int getSuspectCodeLine() const = 0;

	virtual int getGenericsCount() const = 0;

	virtual int getPortsCount() const = 0;

	virtual int getWiresCount() const = 0;

	virtual std::string const & getInstanceName() const = 0;

	virtual void setPortAsWire(
			OvlCheckerPortKind::Kind _type
		,	std::string const & _lhs
		,	std::string const & _rhs
		,	int _width
	) = 0;

	virtual void addInnerDeclaration(
			std::string const & _lhs
		,	std::string const & _rhs
		,	int _width
	) = 0;

	virtual boost::optional< OvlCheckerGenericParameter& >
	getGeneric( GenericType::Kind _type ) const = 0;

	virtual boost::optional < OvlCheckerPort & > getPort(
		OvlCheckerPortKind::Kind _type
	) const = 0;

	virtual void foreachGeneric( GenericParameterCallback const & _functor  ) const = 0;

	virtual void foreachInnerWire( InnerWireCallback const & _functor ) const = 0;

	virtual void foreachPort( PortCallback const & _functor ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_OVL_CHECKER_HPP__
