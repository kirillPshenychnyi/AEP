#ifndef __PORT_IMPL_HPP__
#define __PORT_IMPL_HPP__

/***************************************************************************/

#include "api\vlog_dm_port.hpp"

#include "sources\model\vlog_dm_dimensional_object_impl.hpp"

/***************************************************************************/

namespace VlogDM
{
	struct Dimension;
}

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

class PortImpl
	:	public DimensionalObjectImpl< Port >
{

/***************************************************************************/

	typedef
		DimensionalObjectImpl< Port >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	PortImpl( 
			Declaration const & _declaration
		,	std::unique_ptr< Type > _type
		,	std::string const & _name
		,	Location const & _location
		,	std::unique_ptr< Dimension > _dimension
		,	PortDirection::Direction _direction
	);

/***************************************************************************/

public:

/***************************************************************************/

	PortDirection::Direction getDirection() const override;

	void accept( DeclaredVisitor& _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	const PortDirection::Direction m_direction;

/***************************************************************************/

};

/***************************************************************************/

inline
PortDirection::Direction 
PortImpl::getDirection() const
{
	return m_direction;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__PORT_IMPL_HPP__
