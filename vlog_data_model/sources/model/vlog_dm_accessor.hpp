#ifndef __VLOG_DM_ACCESSOR_IMPL_HPP__
#define __VLOG_DM_ACCESSOR_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declarations_container.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_object_factory.hpp"

#include "common_tools\collections\tools_collection_utils.hpp"

#include <boost\functional\hash\hash.hpp>

#include <boost\unordered_set.hpp>

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

class Accessor
	:	public IAccessor
{

/***************************************************************************/

	typedef
		Tools::Collections::NamedHasher< Writable::DesignUnitPtr >
		DesignUnitHasher;

	typedef
		Tools::Collections::NamedComparator< Writable::DesignUnitPtr >
		DesignUnitComparator;

	typedef
		boost::unordered_set< 
				Writable::DesignUnitPtr
			,	DesignUnitHasher
			,	DesignUnitComparator 
		>
		UnitsSet;

/***************************************************************************/

public:

/***************************************************************************/

	Accessor();

	void addUnit( Writable::DesignUnitPtr _unit ) final;

	boost::optional< DesignUnit const & > findUnit( 
		std::string const& _unitName 
	) const final;

	Writable::DesignUnit & getCurrentImportedUnit() final;

	void reset() final;
		
	void regenerateProcess( 
			std::ostream & _stream
		,	Process const & _process 
	) const final;

	void forEachDesignUnit( DesignUnitCallback _callBack ) const final;

/***************************************************************************/

	Writable::ObjectFactory const& getObjectFactory() const final;

/***************************************************************************/

	UnitsSet m_unitsSet;

	Writable::DesignUnit * m_currentImportedUnit;

	std::unique_ptr< Writable::ObjectFactory > m_objectFactory;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_ACCESSOR_IMPL_HPP__

