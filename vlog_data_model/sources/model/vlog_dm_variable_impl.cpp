#include "stdafx.h"

#include "vlog_data_model\sources\model\vlog_dm_variable_impl.hpp"

#include "vlog_data_model\api\vlog_dm_type.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_declared_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

VariableImpl::VariableImpl( 
			Declaration const & _declaration
		,	std::unique_ptr< Type > _type
		,	std::string const & _name
		,	Location const & _location
		,	std::unique_ptr< Dimension > _dimension
		,	bool _isSigned
	)
	:	BaseClass( 
				_declaration
			,	std::move( _type )
			,	_name
			,	_location
			,	std::move( _dimension )
		)
	,	m_isSigned( _isSigned )
{}

/***************************************************************************/

void 
VariableImpl::accept( DeclaredVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}
