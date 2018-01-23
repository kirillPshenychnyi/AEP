#include "stdafx.h"

#include "vlog_data_model\sources\model\vlog_dm_primary_literal_impl.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

PrimaryLiteralImpl::PrimaryLiteralImpl( 
		Location const & _location
	,	std::string const & _value 
	)
	:	BaseClass( _location )
	,	m_value( _value )
{
}

/***************************************************************************/

void 
PrimaryLiteralImpl::accept( ExpressionVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/