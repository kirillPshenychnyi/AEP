
#include "stdafx.h"

#include "aep_model\model\accessor\aep_model_accessor.hpp"
#include "aep_model\model\checkers\aep_model_ovl_checkers_factory_impl.hpp"

namespace AepModel {

/***************************************************************************/

Accessor::Accessor()
	:	m_checkersFactory( std::make_unique< OvlCheckersFactoryImpl >() )
{
}

/***************************************************************************/

}

/***************************************************************************/