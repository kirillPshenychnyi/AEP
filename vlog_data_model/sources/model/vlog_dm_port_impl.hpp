#ifndef __PORT_IMPL_HPP__
#define __PORT_IMPL_HPP__

/***************************************************************************/

#include "api\vlog_dm_port.hpp"

#include "sources\model\vlog_dm_dimensional_impl.hpp"

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
	:	public DimensionalImpl< Port >
{

/***************************************************************************/

	typedef
		DimensionalImpl< Port >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	PortImpl( 
			Declaration const & _declaration
		,	std::string const & _name
		,	Location const & _location
		,	std::unique_ptr< Dimension > _dimension
		,	PortDirection::Direction _direction
		,	NetType::Type _type
	);

/***************************************************************************/

public:

/***************************************************************************/

	PortDirection::Direction getDirection() const override;

	NetType::Type getNetType() const override;

	void accept( DeclaredVisitor& _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	const PortDirection::Direction m_direction;
	const NetType::Type m_type;

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

inline
NetType::Type 
PortImpl::getNetType() const
{
	return m_type;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__PORT_IMPL_HPP__
