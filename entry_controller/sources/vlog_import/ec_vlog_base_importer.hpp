#ifndef __VLOG_BASE_IMPORTER_HPP__
#define __VLOG_BASE_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\ANTLRGenerated\Verilog2001BaseVisitor.h"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace EntryController 
{ 
	namespace Errors 
	{
		struct ImportError;
		struct IImportErrorsSet;
	}
}

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

#define RETURN_ANY			\
	return antlrcpp::Any();

/***************************************************************************/

class BaseImporter 
	:	public Verilog2001BaseVisitor
{

/***************************************************************************/

	typedef
		std::function< void( antlr4::tree::ParseTree & _tree ) >
		ContextCallback;

/***************************************************************************/

public:

/***************************************************************************/

	BaseImporter(
			VlogDM::IAccessor & _accessor 
		,	Errors::IImportErrorsSet & _errorsSet
	);

/***************************************************************************/

	const VlogDM::Location createLocation( antlr4::ParserRuleContext & _ctx ) const;

	void visitEachChildContext( antlr4::ParserRuleContext const& _ctx );

	void addError( std::unique_ptr< Errors::ImportError > _error );

	void forEachChildContext( 
			antlr4::ParserRuleContext const& _ctx
		,	ContextCallback _callBack 
	);

/***************************************************************************/

	VlogDM::IAccessor & takeVlogDataModel();
	Errors::IImportErrorsSet & takeErrorsSet();

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::IAccessor &	m_vlogDataModel;
	Errors::IImportErrorsSet & m_errorsSet;

/***************************************************************************/

};

/***************************************************************************/

inline 
VlogDM::IAccessor &
BaseImporter::takeVlogDataModel()
{
	return m_vlogDataModel;
}

/***************************************************************************/

inline 
Errors::IImportErrorsSet & 
BaseImporter::takeErrorsSet()
{
	return m_errorsSet;
}

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_BASE_IMPORTER_HPP__
