#ifndef __VLOG_DM_WRITABLE_DECLARATION_HPP__
#define __VLOG_DM_WRITABLE_DECLARATION_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_port_declaration.hpp"
#include "vlog_data_model\api\vlog_dm_variable_declaration.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

template < typename _BaseClass >
struct Declaration 
	:	public _BaseClass
{

/***************************************************************************/
	
	virtual ~Declaration() = default;

	virtual void addDeclared( std::unique_ptr< Declared > _declared ) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct PortDeclaration
	:	Declaration< VlogDM::PortDeclaration >
{

};

/***************************************************************************/

struct VariableDeclaration
	:	Declaration< VlogDM::VariableDeclaration >
{

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_WRITABLE_DECLARATION_HPP__
