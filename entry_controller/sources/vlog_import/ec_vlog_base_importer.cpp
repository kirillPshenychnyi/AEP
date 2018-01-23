#include "stdafx.h"

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_location.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

BaseImporter::BaseImporter( VlogDM::IAccessor & _accessor )
	:	m_vlogDataModel( _accessor )
{
}

/***************************************************************************/

const VlogDM::Location 
BaseImporter::createLocation( antlr4::ParserRuleContext & _ctx ) const
{
	antlr4::Token const & token = *_ctx.getStart();
	
	return
		std::move(
				VlogDM::Location(
				token.getInputStream()->getSourceName()
			,	token.getLine()
			,	token.getCharPositionInLine()
		)
	);
}

/***************************************************************************/

void 
BaseImporter::acceptEachChildContext( antlr4::ParserRuleContext const& _ctx )
{
	forEachChildContext(
			_ctx
		,	[ & ]( antlr4::tree::ParseTree & _tree ) 
			{
				_tree.accept( this );
			}
	);
}

/***************************************************************************/

void 
BaseImporter::forEachChildContext( 
		antlr4::ParserRuleContext const& _ctx
	,	ContextCallback _callBack 
)
{
	for( auto child : _ctx.children )
		_callBack( *child );
}

/***************************************************************************/

}
}