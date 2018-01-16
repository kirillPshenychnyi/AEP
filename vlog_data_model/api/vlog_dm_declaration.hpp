#ifndef __VLOG_DM_DECLARATION_HPP__
#define __VLOG_DM_DECLARATION_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_located.hpp"
#include "boost\optional.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/
	
	struct Declared;

/***************************************************************************/
	
struct Declaration
	:	public Located
{

/***************************************************************************/
		
public:

/***************************************************************************/

	virtual ~Declaration() {}

	virtual boost::optional< Declared const & > findDeclared( std::string const & _declared ) const = 0;

	virtual int getDeclaredsCount() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
 
#endif // !__VLOG_DM_DECLARATION_HPP__

