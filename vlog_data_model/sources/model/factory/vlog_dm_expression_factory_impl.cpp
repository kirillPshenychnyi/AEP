#include "stdafx.h"

#include "vlog_data_model\sources\model\factory\vlog_dm_expression_factory_impl.hpp"

#include "vlog_data_model\sources\model\vlog_dm_primary_literal_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

std::unique_ptr< PrimaryLiteral > 
ExpressionFactoryImpl::newPrimaryLiteral( 
		Location const & _location
	,	double _value 
) const
{
	return std::make_unique< PrimaryLiteralImpl >( _location, _value );
}

/***************************************************************************/

}
