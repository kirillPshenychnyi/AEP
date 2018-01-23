#ifndef __VLOG_DM_DECLARATIONS_CONTAINER_HPP__
#define __VLOG_DM_DECLARATIONS_CONTAINER_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_located.hpp"

#include <boost\optional.hpp>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct Declaration;
struct Declared;

/***************************************************************************/

struct DeclarationsContainer
	:	public Located
{

/***************************************************************************/

	virtual int getDeclarationsCount() const = 0;

	virtual Declaration const& getDeclaration( int _idx ) const = 0;

	virtual boost::optional< Declared const& > findDeclared( 
			std::string const & _declared 
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DECLARATIONS_CONTAINER_HPP__
