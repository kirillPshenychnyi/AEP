#include "stdafx.h"

#include "vlog_data_model\sources\regenerators\vlog_dm_base_regenerator.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Regenerators {

/***************************************************************************/

BaseRegenerator::BaseRegenerator( std::ostream & _targetStream )
	:	m_targetStream( _targetStream )
{
}

/***************************************************************************/

}
}