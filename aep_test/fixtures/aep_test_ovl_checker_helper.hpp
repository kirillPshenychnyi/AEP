#ifndef __AEP_TEST_OVL_CHECKER_HELPER_HPP__
#define __AEP_TEST_OVL_CHECKER_HELPER_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_fwd.hpp"

#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_generic_type.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_port_kind.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_generic_parameter.hpp"

#include "aep_test\fixtures\aep_test_generic_object_helper.hpp"

#include "boost\functional\hash.hpp"

/***************************************************************************/

namespace AepTest {

/***************************************************************************/

class AssertionContextHelper;

/***************************************************************************/

class OvlCheckerHelper
	:	public boost::noncopyable
{

/***************************************************************************/

public:

/***************************************************************************/

	struct InnerWireInfoHasher
	{
		std::size_t operator()( AepModel::OvlChecker::InnerWireInfo const & _info ) const
		{
			std::size_t res = 0;

			boost::hash_combine( res, _info.m_lhs );
			boost::hash_combine( res, _info.m_rhs );
			boost::hash_combine( res, _info.m_width );

			return res;
		}
	};

/***************************************************************************/

	struct InnerWireInfoHelper
		:	public GenericObjectHelper< 
							OvlCheckerHelper
						,	AepModel::OvlChecker::InnerWireInfo
						,	InnerWireInfoHasher 
					>
	{
		typedef 
			GenericObjectHelper< 
					OvlCheckerHelper
				,	AepModel::OvlChecker::InnerWireInfo
				,	InnerWireInfoHasher 
			>
			BaseClass;

		InnerWireInfoHelper( OvlCheckerHelper & _helper )
			:	BaseClass( 
						_helper 
					,	std::bind(
								&AepModel::OvlChecker::foreachInnerWire
							,	std::ref( _helper.getChecker() )
							,	std::placeholders::_1
						)
				)
		{

		}
	};

/***************************************************************************/

public:

/***************************************************************************/

	OvlCheckerHelper(
			AepModel::OvlChecker const & _checker
		,	AssertionContextHelper & _parent
	);

/***************************************************************************/

	AepModel::OvlChecker const & getChecker() const;

	OvlCheckerHelper & id( AepModel::OvlCheckerIds::Kind _id );

	OvlCheckerHelper & instanceName( std::string const & _instName );

	OvlCheckerHelper & suspectLine( int _line );

	OvlCheckerHelper & ports( int _portsCount );

	OvlCheckerHelper & port( 
			AepModel::OvlCheckerPortKind::Kind _portKind
		,	std::string const & _value
	);

	OvlCheckerHelper & genericsParameters( int _genericsCount );

	template < typename _TGeneric >
	OvlCheckerHelper & genericParameter( 
			AepModel::GenericType::Kind _kind 
		,	typename _TGeneric::Kind _value
	)
	{
		auto paramOpt = m_checker.getGeneric( _kind );
	
		REQUIRE( paramOpt.is_initialized() );
	
		return 
			check( 
					paramOpt->valueToString()
				,	std::string( _TGeneric::toString( _value ) )
				,	AepModel::GenericType::toString( _kind )
			);
	}
	
	InnerWireInfoHelper & innerWires();

	AssertionContextHelper & end();

/***************************************************************************/

private:

/***************************************************************************/

	template< typename _TParameter >
	OvlCheckerHelper & check( 
			_TParameter const & _actual
		,	_TParameter const & _expected
		,	std::string const & _paramName
	);

/***************************************************************************/

private:

/***************************************************************************/

	AepModel::OvlChecker const & m_checker;

	AssertionContextHelper & m_parent;

	std::unique_ptr< InnerWireInfoHelper > m_innerWireInfoHelper;

/***************************************************************************/

};

/***************************************************************************/

inline 
AepModel::OvlChecker const & 
OvlCheckerHelper::getChecker() const
{
	return m_checker;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_TEST_OVL_CHECKER_HELPER_HPP__
