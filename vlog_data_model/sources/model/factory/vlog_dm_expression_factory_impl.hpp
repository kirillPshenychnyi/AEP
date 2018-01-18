#ifndef __VLOG_DM_EXPRESSION_FACTORY_IMPL_HPP__
#define __VLOG_DM_EXPRESSION_FACTORY_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_expression_factory.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class ExpressionFactoryImpl
	:	public Writable::ExpressionFactory
{

/***************************************************************************/

public:

/***************************************************************************/

	std::unique_ptr< PrimaryLiteral > newPrimaryLiteral(
			Location const& _location 
		,	double _value
	) const override;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_FACTORY_IMPL_HPP__
