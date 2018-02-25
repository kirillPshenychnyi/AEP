#ifndef __EC_VLOG_BASE_NET_IMPORTER_HPP__
#define __EC_VLOG_BASE_NET_IMPORTER_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"
#include "entry_controller\sources\vlog_import\ec_vlog_net_extractor.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_declaration.hpp"

#include "vlog_data_model\api\vlog_dm_port_directrion.hpp"

#include <boost\function.hpp>

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

template< typename _Declaration >
class BaseNetImporter
	:	public BaseImporter
{

/***************************************************************************/

	typedef
		std::unique_ptr< _Declaration >
		DeclarationPtr;

	typedef
		std::vector< DeclarationPtr >
		ExtractedDeclarations;

	typedef
		boost::function< 
			VlogDM::DeclaredPtr( 
					VlogDM::Declaration &
				,	VlogDM::DimensionPtr
				,	NetExtractor::NetItem 
			) 
		>
		DeclaredCreator;

/***************************************************************************/

protected:

/***************************************************************************/

	BaseNetImporter( VlogDM::IAccessor & _accessor );

/***************************************************************************/

	void addDeclareds( 
			antlr4::ParserRuleContext & _context
		,	DeclaredCreator _creator
	);

	void addDeclarations();

/***************************************************************************/

	virtual DeclarationPtr createDeclaration( 
			VlogDM::Location const & _location
		,	VlogDM::TypePtr _type 
	) = 0;

/***************************************************************************/

protected:

/***************************************************************************/
	
	ExtractedDeclarations m_extractedDeclarations;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_BASE_NET_IMPORTER_HPP__
