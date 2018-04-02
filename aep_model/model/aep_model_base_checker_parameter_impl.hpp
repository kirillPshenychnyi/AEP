#ifndef __AEP_MODEL_BASE_CHECKER_PARAMETER_IMPL_HPP__
#define __AEP_MODEL_BASE_CHECKER_PARAMETER_IMPL_HPP__

/***************************************************************************/

#include "aep_model\api\checkers\checker_values\aep_model_ovl_checker_integer_parameter.hpp"
#include "aep_model\api\checkers\checker_values\aep_model_ovl_checker_string_parameter.hpp"

#include "aep_model\api\checkers\checker_values\aep_model_generic_type.hpp"
#include "aep_model\ih\visitors\aep_model_checker_generic_visitor.hpp"

#include <boost/lexical_cast.hpp>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

template< typename _BaseParam, typename _Val, typename _RVal >
class BaseCheckerParameterImpl
	: public _BaseParam
{

/***************************************************************************/

public:

/***************************************************************************/

	BaseCheckerParameterImpl( _RVal _value, GenericType::Kind _kind )
		:	m_value( _value )
		,	m_kind( _kind )
	{
	}

	void setValue( _RVal _value ) final
	{
		m_value = _value;
	}

	void accept( OvlCheckerGenericVisitor & _visitor ) const final
	{
		_visitor.visit( *this );
	}

	std::string kindToString() const final
	{
		return GenericType::toString( m_kind );
	}

	std::string valueToString() const override
	{
		return valueToString< _Val >();
	}

	template < typename _T >
	std::string valueToString() const
	{
		// stub
		return "";
	}

	template<>
	std::string valueToString< int >() const
	{
		return boost::lexical_cast< std::string >( m_value );
	}

	template<>
	std::string valueToString< std::string >() const
	{
		return m_value;
	}

	_RVal getValue() const final
	{
		return m_value;
	}

	GenericType::Kind getKind() const final
	{
		return m_kind;
	}

	bool isRedefined() const final
	{
		return false;
	}

/***************************************************************************/

private:

/***************************************************************************/

	_Val m_value;
	
	GenericType::Kind m_kind;

/***************************************************************************/

};

/***************************************************************************/

typedef
	BaseCheckerParameterImpl< OvlCheckerIntegerParameter, int, int >
	IntegerParameterImpl;

/***************************************************************************/

class MsgParameterImpl
	:	public BaseCheckerParameterImpl< OvlCheckerStringParameter, std::string, std::string const & >
{

/***************************************************************************/

	typedef
		BaseCheckerParameterImpl< OvlCheckerStringParameter, std::string, std::string const & >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	MsgParameterImpl()
		:	BaseClass( "Error", GenericType::Kind::Msg )
	{
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/
 
#endif // !__AEP_MODEL_BASE_CHECKER_PARAMETER_IMPL_HPP__
