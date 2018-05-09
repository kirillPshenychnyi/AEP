#include "stdafx.h"

#include "entry_controller\api\errors\ec_ibase_import_error.hpp"
#include "entry_controller\api\errors\ec_iimport_errors_set.hpp"

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_location.hpp"

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

BaseImporter::BaseImporter( 
		VlogDM::IAccessor & _accessor 
	,	Errors::IImportErrorsSet & _errorsSet
)
	:	m_vlogDataModel( _accessor )
	,	m_errorsSet( _errorsSet )
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
BaseImporter::visitEachChildContext( antlr4::ParserRuleContext const& _ctx )
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
BaseImporter::addError( std::unique_ptr< Errors::ImportError > _error )
{
	m_errorsSet.addError( std::move( _error ) );
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