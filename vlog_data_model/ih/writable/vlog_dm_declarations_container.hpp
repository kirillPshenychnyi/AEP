#ifndef __VLOG_DM_WRITABLE_DECLARATIONS_CONTAINER_HPP__
#define __VLOG_DM_WRITABLE_DECLARATIONS_CONTAINER_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_design_unit.hpp"
#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

template< typename _BaseClass >
struct DeclarationsContainer
	:	public _BaseClass
{

/***************************************************************************/

	virtual void addDeclaration( 
			std::unique_ptr< VlogDM::Declaration > _declContainer 
	) = 0;

/***************************************************************************/

};

/***************************************************************************/

struct DesignUnit
	:	public DeclarationsContainer< VlogDM::DesignUnit >
{ 

/***************************************************************************/

	virtual void addProcess( ProcessPtr _process ) = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__VLOG_DM_WRITABLE_DECLARATIONS_CONTAINER_HPP__S

