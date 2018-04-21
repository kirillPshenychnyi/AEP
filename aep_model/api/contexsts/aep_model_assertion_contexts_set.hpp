#ifndef __AEP_MODEL_ASSERTION_CONTEXT_SET_HPP__
#define __AEP_MODEL_ASSERTION_CONTEXT_SET_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

#include "aep_model\api\aep_model_fwd.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct AssertionContextSet
	:	public boost::noncopyable
{

/***************************************************************************/

	typedef
		std::function< void( AssertionContext const & ) >
		AssertionContextCallback;

/***************************************************************************/

	virtual void addContext( AssertionContextPtr _context ) = 0;

	virtual bool hasAssertionContext( std::string const & _dutName ) const = 0;

	virtual void forEachAssertionContext( AssertionContextCallback _callBack ) const = 0;

	virtual boost::optional< AssertionContext & > takeContext( 
		std::string const & _dutName 
	) = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_ASSERTION_CONTEXT_SET_HPP__
