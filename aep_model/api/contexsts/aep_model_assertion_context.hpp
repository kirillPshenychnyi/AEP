#ifndef __AEP_MODEL_ASSERTION_CONTEXT_HPP__
#define __AEP_MODEL_ASSERTION_CONTEXT_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_fwd.hpp"

#include <functional>
#include <boost\functional\hash.hpp>
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

		bool operator == ( PortInfo const & _other ) const 
		{
			return 
					m_width == _other.m_width
				&&	m_portName == _other.m_portName
				&&	m_portValue == _other.m_portValue;
		}

		const std::string m_portName;
		const std::string m_portValue;
		int m_width;
	};

	struct PortInfoHasher
	{	
		std::size_t operator() ( PortInfo const & _info ) const 
		{
			std::size_t seed;

			boost::hash_combine( seed, _info.m_portName );
			boost::hash_combine( seed, _info.m_portValue );
			boost::hash_combine( seed, _info.m_width );

			return seed;
		}
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

	virtual ~AssertionContext() = default;

	virtual std::string const & getDUTName() const = 0;

	virtual void addInputPort( 
			std::string const&  _portName 
		,	std::string const& _portValue
		,	int _width 
	) = 0;

	virtual void addInstanceName( std::string const & _name ) = 0;

	virtual void addChecker( OvlCheckerPtr _checker ) = 0;

	virtual int getCheckerCount() const = 0;

	virtual OvlChecker const & getChecker( int _idx ) const = 0;

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
