#ifndef __VLOG_DM_ITEMS_FACTORY_IMPL_HPP__
#define __VLOG_DM_ITEMS_FACTORY_IMPL_HPP__
 
/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_items_factory.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ItemsFactoryImpl
	:	public Writable::ItemsFactory
{

/***************************************************************************/

public:

/***************************************************************************/

	std::unique_ptr< Dimension > newPackedDimension( 
			Location const& _location
		,	std::unique_ptr< Range > _range
	) const override;

	std::unique_ptr< Range > newExpressionRange( 
			Location const& _location
		,	std::unique_ptr< Expression > _lhs
		,	std::unique_ptr< Expression > _rhs
	) const override;

/***************************************************************************/

};
	
/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_ITEMS_FACTORY_IMPL_HPP__
