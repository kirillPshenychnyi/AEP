#ifndef __AEP_TEST_ASSERTION_CONTEXT_HELPER_HPP__
#define __AEP_TEST_ASSERTION_CONTEXT_HELPER_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_fwd.hpp"

#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"

#include "aep_test\fixtures\aep_test_ovl_checker_helper.hpp"

#include "aep_test\fixtures\aep_test_generic_object_helper.hpp"

/***************************************************************************/

namespace AepTest {

/***************************************************************************/

class AssertionContextHelper
	:	public boost::noncopyable
{

/***************************************************************************/

class InstanceHelper
	:	public GenericObjectHelper< AssertionContextHelper, std::string >
{

/***************************************************************************/

public:

/***************************************************************************/

	using BaseClass = GenericObjectHelper< AssertionContextHelper, std::string >;

	InstanceHelper( AssertionContextHelper & _ctxHelper )
		:	BaseClass( 
					_ctxHelper
				,	std::bind( 
							&AepModel::AssertionContext::forEachInstance 
						,	std::ref( _ctxHelper.getAssertionContext() )
						,	std::placeholders::_1
					)
			)
	{
	}

/***************************************************************************/

};

/***************************************************************************/

class PortHelper
	:	public GenericObjectHelper< 
				AssertionContextHelper
			,	AepModel::AssertionContext::PortInfo 
			,	AepModel::AssertionContext::PortInfoHasher
		>
{

/***************************************************************************/

	typedef 
		GenericObjectHelper< 
				AssertionContextHelper
			,	AepModel::AssertionContext::PortInfo
			,	AepModel::AssertionContext::PortInfoHasher 
		> 
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	PortHelper( AssertionContextHelper & _ctxHelper )
		:	BaseClass( 
					_ctxHelper
				,	std::bind( 
							&AepModel::AssertionContext::forEachInputPort 
						,	std::ref( _ctxHelper.getAssertionContext() )
						,	std::placeholders::_1
					)
			)
	{
	}

/***************************************************************************/

};

/***************************************************************************/

public:

/***************************************************************************/

	AssertionContextHelper( AepModel::AssertionContext const & _context );

/***************************************************************************/

	InstanceHelper & instances();

	PortHelper & ports();

	OvlCheckerHelper & checker( int _checker );

	AepModel::AssertionContext const & getAssertionContext() const;

/***************************************************************************/

private:

/***************************************************************************/

	AepModel::AssertionContext const & m_context;

	std::unique_ptr< InstanceHelper > m_instanceHelper;

	std::unique_ptr< PortHelper > m_portHelper;

	std::unique_ptr< OvlCheckerHelper > m_checkerHelper;

/***************************************************************************/

};

/***************************************************************************/

inline
AepModel::AssertionContext const & 
AssertionContextHelper::getAssertionContext() const
{
	return m_context;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_TEST_ASSERTION_CONTEXT_HELPER_HPP__
