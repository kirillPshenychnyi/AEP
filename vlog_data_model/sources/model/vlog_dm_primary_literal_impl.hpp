#ifndef __VLOG_DM_PRIMARY_LITERAL_IMPL_HPP__
#define __VLOG_DM_PRIMARY_LITERAL_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

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
		,	double _value 
	);

/***************************************************************************/

	double getValue() const override;
	
	void accept( ExpressionVisitor & _visitor ) override;

/***************************************************************************/

private:

/***************************************************************************/

	const double m_value;

/***************************************************************************/

};

/***************************************************************************/

inline 
PrimaryLiteralImpl::PrimaryLiteralImpl(
		Location const & _location
	,	double _value
	)
	:	BaseClass( _location )
	,	m_value( _value )
{
}

/***************************************************************************/

inline
double 
PrimaryLiteralImpl::getValue() const
{
	return m_value;
}

/***************************************************************************/

inline
void PrimaryLiteralImpl::accept( ExpressionVisitor & _visitor )
{
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_PRIMARY_LITERAL_IMPL_HPP__
