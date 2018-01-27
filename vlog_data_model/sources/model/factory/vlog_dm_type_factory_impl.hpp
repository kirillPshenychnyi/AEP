#ifndef __VLOG_DM_TYPE_FACTORY_IMPL_HPP__
#define __VLOG_DM_TYPE_FACTORY_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_type_factory.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class TypeFactoryImpl
	:	public Writable::TypeFactory
{

/***************************************************************************/

	std::unique_ptr< NetType > newNetType(
			NetKind::Kind _netKind
		,	std::unique_ptr< Dimension > _dimension
	) const override;

	std::unique_ptr< VariableType > newVariableType(
			VariableKind::Kind _netKind
		,	std::unique_ptr< Dimension > _dimension
	) const override;

/***************************************************************************/

private:

/***************************************************************************/

	template< typename _Type, class _Kind >
	std::unique_ptr< _Type > newType(
			typename _Kind::Kind _netKind
		,	std::unique_ptr< Dimension > _dimension
	) const;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_TYPE_FACTORY_IMPL_HPP__
