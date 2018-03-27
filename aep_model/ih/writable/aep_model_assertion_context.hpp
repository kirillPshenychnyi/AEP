#ifndef __AEP_MODEL_WRITABLE_ASSERTION_CONTEXT_HPP__
#define __AEP_MODEL_WRITABLE_ASSERTION_CONTEXT_HPP__

/***************************************************************************/

#include "aep_model\api\contexsts\aep_model_instance_based_context.hpp"

/***************************************************************************/

namespace AepModel 
{

/***************************************************************************/

struct ReferencedSignalInfo;
struct InnerSignalInfo;

/***************************************************************************/

}

/***************************************************************************/

namespace AepModel {
namespace Writable {

/***************************************************************************/

template< typename _BaseContext >
struct AssertionContext
	:	public _BaseContext
{

/***************************************************************************/


/***************************************************************************/

};

/***************************************************************************/

struct InstanceBasedContext
	:	public AssertionContext< AepModel::AssertionContext >
{

/***************************************************************************/

	virtual void addReferencedSignal( ReferencedSignalInfo const & _info ) const = 0;
	
	virtual void addInnerSignal( InnerSignalInfo const & _info ) const = 0;
	
/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__AEP_MODEL_WRITABLE_ASSERTION_CONTEXT_HPP__

