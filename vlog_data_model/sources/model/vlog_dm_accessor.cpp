#include "stdafx.h"

#include "vlog_data_model\sources\model\vlog_dm_accessor.hpp"

#include "vlog_data_model\api\vlog_dm_process.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"

#include "vlog_data_model\sources\model\factory\vlog_dm_object_factory_impl.hpp"

#include "vlog_data_model\sources\regenerators\vlog_dm_process_regenerator.hpp"
#include "vlog_data_model\sources\regenerators\vlog_dm_expression_regenerator.hpp"

#include "vlog_data_model\sources\vlog_engines\vlog_dm_bitwidth_calculator.hpp"

#include <sstream>

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

std::string 
Accessor::regenerateExpression( Expression const & _expression ) const
{
	std::stringstream output;

	Regenerators::ExpressionRegenerator regenerator( output );

	_expression.accept( regenerator );

	return output.str();
}

/***************************************************************************/

void
Accessor::forEachDesignUnit( DesignUnitCallback _callBack ) const
{
	for( auto const & unit : m_unitsSet )
		_callBack( *unit );
}

/***************************************************************************/

int 
Accessor::calculateBitwidth( Expression const & _expression ) const
{
	VlogEngines::BitwidthCalculator calculator;

	return calculator.calculate( _expression );
}

/***************************************************************************/

int
Accessor::calculateBitwidth( BaseIdentifier const & _id ) const
{
	VlogEngines::BitwidthCalculator calculator;

	return calculator.calculate( _id.getDeclared() );
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
