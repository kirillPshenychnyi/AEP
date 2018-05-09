#ifndef __EC_ACCESSOR_HPP__
#define __EC_ACCESSOR_HPP__

/***************************************************************************/

#include "entry_controller\api\ec_iaccessor.hpp"
#include "entry_controller\api\errors\ec_iimport_errors_set.hpp"

#include <boost\unordered_set.hpp>

/***************************************************************************/

namespace VlogDM 
{
	struct IAccessor;
}

namespace Aep 
{
	struct IAccessor;
}

/***************************************************************************/

namespace EntryController {

/***************************************************************************/

class Accessor
	:	public IAccessor
{

/***************************************************************************/

public:

/***************************************************************************/

	Accessor(
			const std::shared_ptr< VlogDM::IAccessor > _vlogDm
		,	const std::shared_ptr< Aep::IAccessor > _aepAccessor
	);

	~Accessor() = default;

/***************************************************************************/

public:

/***************************************************************************/

	bool importVerilog( std::string const & _code ) final;
	
	void addFile( std::string const & _path ) final;

	bool runVerilogImport();

	void runAepAnalysis(
			Aep::IAccessor::GlobalClockParameters & _clockParams
		,	boost::optional< Aep::IAccessor::GlobalResetParameters const & > _resetParams
	) final;

	Errors::IImportErrorsSet const& getImportErrors() const final;

	void dumpErrors( std::ostream & _output ) const;

/***************************************************************************/

private:

/***************************************************************************/

	void reset();
	
	template< typename _TStream >
	bool runImport( _TStream & _stream, std::string const & _name );

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::IAccessor & m_vlogDm;

	Aep::IAccessor & m_aepAccessor;

	std::unique_ptr< Errors::IImportErrorsSet > m_importErrors;

	boost::unordered_set< std::string > m_designFiles;

/***************************************************************************/

};

/***************************************************************************/

inline
Errors::IImportErrorsSet const& 
Accessor::getImportErrors() const
{
	return *m_importErrors;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__EC_ACCESSOR_HPP__
