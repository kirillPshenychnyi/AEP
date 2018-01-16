#ifndef __DECLARED_FACTORY_HPP__
#define __DECLARED_FACTORY_HPP__

/***************************************************************************/

#include "ih\writable\vlog_dm_declared_factory.hpp"

/***************************************************************************/

namespace VlogDM { 

/***************************************************************************/

class DeclaredFactoryImpl
	:	public Writable::DeclaredFactory
{

/***************************************************************************/

public:

/***************************************************************************/

	virtual std::unique_ptr< Port > newPort ( 
			Declaration const & _declaration
		,	std::string const & _name
		,	Location const & _location
		,	PortDirection::Direction _direction
		,	std::unique_ptr< Dimension > _dimension
	) const;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__DECLARED_FACTORY_HPP__
