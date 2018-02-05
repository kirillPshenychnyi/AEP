#ifndef __DECLARED_FACTORY_HPP__
#define __DECLARED_FACTORY_HPP__

/***************************************************************************/

#include "vlog_data_model\ih\writable\vlog_dm_declared_factory.hpp"

/***************************************************************************/

namespace VlogDM { 

/***************************************************************************/

class DeclaredFactoryImpl
	:	public Writable::DeclaredFactory
{

/***************************************************************************/

public:

/***************************************************************************/

	PortPtr newPort ( 
			Declaration const & _declaration_type
		,	std::string const & _name
		,	Location const & _location
		,	PortDirection::Direction _direction
		,	DimensionPtr _dimension
	) const override;

	VariablePtr newVariable ( 
			VlogDM::Declaration const & _declaration
		,	std::string const & _name
		,	Location const & _location
		,	bool _isSigned
		,	DimensionPtr _dimension
	) const override;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__DECLARED_FACTORY_HPP__
