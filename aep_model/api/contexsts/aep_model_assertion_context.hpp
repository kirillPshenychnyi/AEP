#ifndef __AEP_MODEL_ASSERTION_CONTEXT_HPP__
#define __AEP_MODEL_ASSERTION_CONTEXT_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_fwd.hpp"

#include <boost\noncopyable.hpp>

#include <functional>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct AssertionContext
	:	public boost::noncopyable
{

/***************************************************************************/

	struct PortInfo
	{
		PortInfo( 
				std::string const&  _portName 
			,	std::string const& _portValue
			,	int _width
		)
			:	m_portName( _portName )
			,	m_portValue( _portValue )
			,	m_width( _width )
		{
		}

		const std::string m_portName;
		const std::string m_portValue;

		int m_width;
	};

/***************************************************************************/

	typedef
		std::function< void( std::string const & ) >
		InstanceCallback;

	typedef
		std::function< void( PortInfo const & ) >
		InputPortCallback;

	typedef
		std::function< void( OvlChecker const & ) >
		CheckerCallback;

/***************************************************************************/

	virtual std::string const & getDUTName() const = 0;

	virtual void addInputPort( 
			std::string const&  _portName 
		,	std::string const& _portValue
		,	int _width 
	) = 0;

	virtual void addInstanceName( std::string const & _name ) = 0;

	virtual void addChecker( OvlCheckerPtr _checker ) = 0;

	virtual void forEachInstance( InstanceCallback _callBack ) const = 0;
	
	virtual void forEachInputPort( InputPortCallback _callback ) const = 0;

	virtual void forEachChecker( CheckerCallback _callback ) const = 0;

	virtual int getInputsCount() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_ASSERTION_CONTEXT_HPP__
