#include "stdafx.h"

#include "vlog_data_model\api\vlog_dm_type.hpp"

#include "vlog_data_model\sources\model\factory\vlog_dm_declared_factory_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_port_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_variable_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

PortPtr
DeclaredFactoryImpl::newPort( 
		Declaration const & _declaration
	,	std::string const & _name
	,	Location const & _location
	,	PortDirection::Direction _direction
	,	DimensionPtr _dimension 
	) const
{	
	return
		std::make_unique< PortImpl >(
				_declaration
			,	_name
			,	_location
			,	std::move( _dimension )
			,	_direction
		);
}

/***************************************************************************/

VariablePtr
DeclaredFactoryImpl::newVariable ( 
		VlogDM::Declaration const & _declaration
	,	std::string const & _name
	,	Location const & _location
	,	bool _isSigned
	,	DimensionPtr _dimension
	) const
{
	return
		std::make_unique< VariableImpl >(
				_declaration
			,	_name
			,	_location
			,	std::move( _dimension )
			,	_isSigned
		);
}

/***************************************************************************/

}