#ifndef __VLOG_DM_EXPRESSION_FACTORY_HPP__
#define __VLOG_DM_EXPRESSION_FACTORY_HPP__

/***************************************************************************/

#include <boost\noncopyable.hpp>

/***************************************************************************/

namespace VlogDM 
{
	struct Location;
	struct PrimaryLiteral;
}

/***************************************************************************/

namespace VlogDM {
namespace Writable {

/***************************************************************************/

struct ExpressionFactory
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual std::unique_ptr< PrimaryLiteral > newPrimaryLiteral(
			Location const& _location 
		,	std::string const& _value
	) const = 0;

/***************************************************************************/

};

/***************************************************************************/

}
}


/***************************************************************************/

#endif // !__VLOG_DM_EXPRESSION_FACTORY_HPP__
