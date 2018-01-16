#ifndef __VLOG_DM_DECLARATION_FACTORY_HPP__
#define __VLOG_DM_DECLARATION_FACTORY_HPP__

/***************************************************************************/

#include "boost\noncopyable.hpp"

/***************************************************************************/

namespace VlogDM
{
	namespace Writable
	{
		struct PortDeclaration;
	}

	struct Location;
}

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct DeclarationFactory 
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual ~DeclarationFactory() {}

	virtual std::unique_ptr< Writable::PortDeclaration > newPortDeclaration( 
			Location const & _location 
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !_VLOG_DM_DECLARATION_FACTORY_HPP__
