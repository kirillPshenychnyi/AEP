#ifndef __VLOG_DM_DECLARATION_FACTORY_HPP__
#define __VLOG_DM_DECLARATION_FACTORY_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct DeclarationFactory 
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual ~DeclarationFactory() = default;

	virtual Writable::PortDeclarationPtr newPortDeclaration( 
			Location const & _location 
		,	TypePtr _type
	) const = 0;

	virtual Writable::VariableDeclarationPtr newVariableDeclaration(
			Location const & _location 
		,	TypePtr _type
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !_VLOG_DM_DECLARATION_FACTORY_HPP__
