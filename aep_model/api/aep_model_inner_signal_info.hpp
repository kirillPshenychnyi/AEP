#ifndef __AEP_MODEL_INNER_SIGNAL_INFO_HPP__
#define __AEP_MODEL_INNER_SIGNAL_INFO_HPP__

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct InnerSignalInfo
{

/***************************************************************************/

	virtual std::string const & getLhs() const = 0;

	virtual std::string const & getRhs() const = 0;

	virtual int getWidth() const = 0;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_SIGNAL_DECLARATION_INFO_HPP__
