#ifndef __AEP_MODEL_REFERENCED_SIGNAL_INFO_HPP__
#define __AEP_MODEL_REFERENCED_SIGNAL_INFO_HPP__

/***************************************************************************/

#include "boost\noncopyable.hpp"

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct ReferencedSignalInfo
	:	public boost::noncopyable
{

/***************************************************************************/

	virtual std::string const & getName() const = 0;
	
	virtual std::string const & getReferencePattern() const = 0;

	virtual int getWidth() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_REFERENCED_SIGNAL_INFO_HPP__
