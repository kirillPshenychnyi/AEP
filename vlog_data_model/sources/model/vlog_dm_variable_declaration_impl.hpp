#ifndef __VLOG_DM_VARIABLE_DECLARATION_IMPL_HPP__
#define __VLOG_DM_VARIABLE_DECLARATION_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\visitors\vlog_dm_declaration_visitor.hpp"
#include "vlog_data_model\ih\writable\vlog_dm_declaration.hpp"

#include "vlog_data_model\sources\model\vlog_dm_declaration_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class VariableDeclarationImpl
	:	public DeclarationImpl< Writable::VariableDeclaration >
{

/***************************************************************************/

	typedef
		DeclarationImpl< Writable::VariableDeclaration >
		BaseClass;
	
/***************************************************************************/

public:

/***************************************************************************/

	VariableDeclarationImpl( Location const & _location, TypePtr _type )
		:	BaseClass( _location, std::move( _type ) )
	{
	}
	
	void accept( DeclarationVisitor & _visitor ) const final
	{
		_visitor.visit( *this );
	}

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_VARIABLE_DECLARATION_IMPL_HPP__
