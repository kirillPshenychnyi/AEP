#include "stdafx.h"

#include "vlog_data_model\api\vlog_dm_dimension.hpp"

#include "vlog_data_model\sources\model\factory\vlog_dm_type_factory_impl.hpp"

#include "vlog_data_model\sources\model\vlog_dm_net_type_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_variable_type_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

std::unique_ptr< NetType >
TypeFactoryImpl::newNetType( 
		NetKind::Kind _netKind
	,	std::unique_ptr< Dimension > _dimension 
) const
{ 
	return newType< NetTypeImpl, NetKind >( _netKind, std::move( _dimension ) );
}

/***************************************************************************/

std::unique_ptr< VariableType > 
TypeFactoryImpl::newVariableType( 
		VariableKind::Kind _netKind
	,	std::unique_ptr< Dimension > _dimension 
) const
{
	return newType< VariableTypeImpl, VariableKind >( _netKind, std::move( _dimension ) );
}

/***************************************************************************/

template< typename _Type, class _Kind >
std::unique_ptr< _Type >
TypeFactoryImpl::newType( 
		typename _Kind::Kind _netKind
	,	std::unique_ptr< Dimension > _dimension 
) const
{
	return std::make_unique< _Type >( std::move( _dimension ), _netKind );
}

/***************************************************************************/

}