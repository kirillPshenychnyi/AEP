#ifndef __AEP_MODEL_ASSERTION_CONTEXT_SET_HPP__
#define __AEP_MODEL_ASSERTION_CONTEXT_SET_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_fwd.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct AssertionContextSet
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual ~AssertionContextSet() = default;

	virtual void addContext( AssertionContextPtr _context ) = 0;

	virtual bool hasAssertionContext( std::string const & _dutName ) const = 0;

	virtual void forEachAssertionContext( AssertionContextCallback _callBack ) const = 0;

	virtual void forEachAssertionContext( ConstAssertionContextCallback _callBack ) = 0;

	virtual boost::optional< AssertionContext & > takeContext( 
		std::string const & _dutName 
	) = 0;

	virtual boost::optional< AssertionContext const & > getContext(
		std::string const & _dutName
	) const = 0;

	virtual void clear() = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_ASSERTION_CONTEXT_SET_HPP__
