#ifndef __VLOG_DM_DECLARATION_HPP__
#define __VLOG_DM_DECLARATION_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_located.hpp"
#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include <boost\optional.hpp>

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

struct DeclarationVisitor;

/***************************************************************************/

struct Declaration
	:	public Located
{

/***************************************************************************/
		
public:

/***************************************************************************/

	virtual boost::optional< Declared const & > 
		findDeclared( std::string const & _declared ) const = 0;

	virtual int getDeclaredsCount() const = 0;

	virtual void accept( DeclarationVisitor & _visitor ) const = 0;
	
	virtual Type const & getType() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
 
#endif // !__VLOG_DM_DECLARATION_HPP__

