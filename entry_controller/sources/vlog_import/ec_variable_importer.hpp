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

	using BaseClass::BaseNetImporter;

/***************************************************************************/
	
	template< typename _DataType >
	void importVars( _DataType & _ctx );

/***************************************************************************/

private:

/***************************************************************************/

	template < typename _Context >
	void importVar( _Context & _ctx );

	VlogDM::Writable::VariableDeclarationPtr createDeclaration( 
			VlogDM::Location const & _location
		,	VlogDM::TypePtr _type 
	) override;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_VARIABLE_IMPORTER_HPP__
