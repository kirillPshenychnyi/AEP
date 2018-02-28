#include "stdafx.h"

#include "vlog_data_model\sources\model\vlog_dm_accessor.hpp"

#include "vlog_data_model\api\vlog_dm_process.hpp"

#include "vlog_data_model\sources\model\factory\vlog_dm_object_factory_impl.hpp"

#include "vlog_data_model\sources\regenerators\vlog_dm_process_regenerator.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

Accessor::Accessor()
	:	m_currentImportedUnit( nullptr )
	,	m_objectFactory( new ObjectFactoryImpl() )
{
}

/***************************************************************************/

void
Accessor::addUnit( Writable::DesignUnitPtr _unit )
{	
	m_currentImportedUnit = _unit.get();
	m_unitsSet.emplace( std::move( _unit ) );
}

/***************************************************************************/

boost::optional< DesignUnit const& >
Accessor::findUnit( std::string const & _unitName ) const
{
	auto findIt 
		=	m_unitsSet.find( 
					_unitName
				,	DesignUnitHasher()
				,	DesignUnitComparator() 
			);

	return 
		findIt == m_unitsSet.end()
	?	boost::optional< DesignUnit const& >()
	:	**findIt;
}

/***************************************************************************/

Writable::DesignUnit &
Accessor::getCurrentImportedUnit()
{
	assert( m_currentImportedUnit );

	return *m_currentImportedUnit;
}

/***************************************************************************/

void 
Accessor::reset()
{
	m_unitsSet.clear();
	m_currentImportedUnit = nullptr;
}

/***************************************************************************/

void 
Accessor::regenerateProcess( std::ostream & _stream, Process const & _process ) const
{
	Regenerators::ProcessRegenerator regenerator( _stream );

	_process.accept( regenerator );
}

/***************************************************************************/

Writable::ObjectFactory const&
Accessor::getObjectFactory() const
{
	assert( m_objectFactory );

	return *m_objectFactory;
}

/***************************************************************************/

}
