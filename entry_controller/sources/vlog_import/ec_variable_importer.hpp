#ifndef __VLOG_VARIABLE_IMPORTER_HPP__
#define __VLOG_VARIABLE_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_net_importer.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declaration.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

class VariableImporter 
	:	public BaseNetImporter< VlogDM::Writable::VariableDeclaration >
{

/***************************************************************************/

	typedef
		BaseNetImporter< VlogDM::Writable::VariableDeclaration >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	VariableImporter(
			VlogDM::IAccessor & _accessor
		,	VlogDM::Writable::DesignUnit & _targetUnit 
	);

/***************************************************************************/

	void importVars( Verilog2001Parser::Net_declarationContext & _ctx );
	
/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitNet_declaration( 
			Verilog2001Parser::Net_declarationContext * _ctx 
	) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_VARIABLE_IMPORTER_HPP__
