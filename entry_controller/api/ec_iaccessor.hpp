#ifndef __EC_IACCESSOR_HPP__
#define __EC_IACCESSOR_HPP__

/***************************************************************************/

#include "aep\api\aep_iaccessor.hpp"
#include "aep\api\aep_checker_ids.hpp"

/***************************************************************************/

namespace EntryController 
{
	namespace Errors 
	{
		struct IImportErrorsSet;
	}
}

/***************************************************************************/

namespace EntryController {

/***************************************************************************/

struct IAccessor
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual ~IAccessor() = default;

	virtual bool importVerilog( std::string const& _code ) = 0;
	
	virtual void addFile( std::string const & _path ) = 0;

	virtual bool runVerilogImport() = 0;

	virtual void runAepAnalysis(
			Aep::CheckerIds _checkers
		,	Aep::IAccessor::GlobalClockParameters & _clockParams
		,	boost::optional< Aep::IAccessor::GlobalResetParameters const & > _resetParams
	) = 0;

	virtual Errors::IImportErrorsSet const& getImportErrors() const = 0;

	virtual void dumpErrors( std::ostream & _output ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__EC_IACCESSOR_HPP__
