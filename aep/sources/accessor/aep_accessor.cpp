#include "stdafx.h"

#include "aep\sources\accessor\aep_accessor.hpp"
#include "aep\checkers\aep_full_case_syn_directive_checker.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

Accessor::Accessor(
		std::shared_ptr< VlogDM::IAccessor > _vlogDm 
	,	std::shared_ptr< AepModel::IAccessor > _aepModel
)
	:	m_vlogDm( *_vlogDm )
	,	m_aepModel( *_aepModel )
{
}

/***************************************************************************/

void
Accessor::runEngine()
{
	FullCaseSynDirectiveChecker c1( *this );

	c1.analyze();
}

/***************************************************************************/

}