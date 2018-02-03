#ifndef __VLOG_DM_DECLARED_HPP__
#define __VLOG_DM_DECLARED_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_located.hpp"
#include "vlog_data_model\api\vlog_dm_named.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

struct Declaration;
struct Type;
struct DeclaredVisitor;

/***************************************************************************/
	
struct Declared
	:	public Located
	,	public Named
{

/***************************************************************************/
		
	virtual Declaration const & getDeclaration() const = 0;

	virtual Type const & getType() const = 0;

	virtual void accept( DeclaredVisitor & _visitor ) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // __VLOG_DM_DECLARED_HPP__
