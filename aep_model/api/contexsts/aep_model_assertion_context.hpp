#ifndef __AEP_MODEL_ASSERTION_CONTEXT_HPP__
#define __AEP_MODEL_ASSERTION_CONTEXT_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include <functional>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct AssertionContext
	:	public boost::noncopyable
{

/***************************************************************************/

	typedef
		std::function< void( std::string const & ) >
		InstanceCallback;

/***************************************************************************/

	virtual std::string const & getDUTName() const = 0;

	virtual void addInstanceName ( std::string const & _name ) = 0;

	virtual void forEachInstance( InstanceCallback _callBack ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_ASSERTION_CONTEXT_HPP__
