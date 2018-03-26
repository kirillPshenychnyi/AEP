#ifndef __VLOG_DM_PRIMARY_LITERAL_IMPL_HPP__
#define __VLOG_DM_PRIMARY_LITERAL_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class PrimaryLiteralImpl
	:	public LocatedImpl< PrimaryLiteral >
{

/***************************************************************************/

	typedef
		LocatedImpl< PrimaryLiteral >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	PrimaryLiteralImpl(
			Location const & _location
		,	std::string const& _value 
	);

/***************************************************************************/

	std::string const& getValue() const final;
	
	void accept( ExpressionVisitor & _visitor ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	const std::string m_value;

/***************************************************************************/

};

/***************************************************************************/

inline
PrimaryLiteralImpl::PrimaryLiteralImpl( 
		Location const & _location
	,	std::string const & _value 
	)
	:	BaseClass( _location )
	,	m_value( _value )
{
}

/***************************************************************************/

inline
void 
PrimaryLiteralImpl::accept( ExpressionVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

inline
std::string const&
PrimaryLiteralImpl::getValue() const
{
	return m_value;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_PRIMARY_LITERAL_IMPL_HPP__
