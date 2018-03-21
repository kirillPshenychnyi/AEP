#ifndef __VLOG_BASE_IMPORTER_HPP__
#define __VLOG_BASE_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\ANTLRGenerated\Verilog2001BaseVisitor.h"

/***************************************************************************/

namespace VlogDM
{
	struct Location;
	struct IAccessor;

	namespace Writable 
	{
		struct DesignUnit;
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

protected:

/***************************************************************************/

	BaseImporter( VlogDM::IAccessor & _accessor );

/***************************************************************************/

	const VlogDM::Location createLocation( antlr4::ParserRuleContext & _ctx ) const;

	void visitEachChildContext( antlr4::ParserRuleContext const& _ctx );

	void forEachChildContext( 
			antlr4::ParserRuleContext const& _ctx
		,	ContextCallback _callBack 
	);

/***************************************************************************/

	VlogDM::IAccessor & getVlogDataModel();

/***************************************************************************/

private:

/***************************************************************************/

	VlogDM::IAccessor &	m_vlogDataModel;

/***************************************************************************/

};

/***************************************************************************/

inline 
VlogDM::IAccessor &
BaseImporter::getVlogDataModel()
{
	return m_vlogDataModel;
}

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_BASE_IMPORTER_HPP__
