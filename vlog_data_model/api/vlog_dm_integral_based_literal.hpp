#ifndef __VLOG_DM_INTEGRAL_BASED_LITERAL_HPP__
#define __VLOG_DM_INTEGRAL_BASED_LITERAL_HPP__

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

struct IntegralBasedLiteral
{

/***************************************************************************/

	virtual boost::optional< const int > getSize() const = 0;

	virtual std::string const & getOriginalValue() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_INTEGRAL_BASED_LITERAL_HPP__
