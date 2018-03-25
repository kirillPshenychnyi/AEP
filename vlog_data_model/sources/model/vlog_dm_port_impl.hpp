#ifndef __PORT_IMPL_HPP__
#define __PORT_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_declared_visitor.hpp"

#include "vlog_data_model\sources\model\vlog_dm_dimensional_object_impl.hpp"

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
		,	std::string const & _name
		,	Location const & _location
		,	std::unique_ptr< Dimension > _dimension
		,	PortDirection::Direction _direction
	);

/***************************************************************************/

public:

/***************************************************************************/

	PortDirection::Direction getDirection() const final;

	void accept( DeclaredVisitor& _visitor ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	const PortDirection::Direction m_direction;

/***************************************************************************/

};

/***************************************************************************/

inline
PortImpl::PortImpl( 
		Declaration const & _declaration
	,	std::string const & _name
	,	Location const & _location
	,	std::unique_ptr< Dimension > _dimension
	,	PortDirection::Direction _direction 
	)
	:	BaseClass( 
				_declaration
			,	_name
			,	_location
			,	std::move( _dimension )
		)
	,	m_direction( _direction )
{
}

/***************************************************************************/

inline
void 
PortImpl::accept( DeclaredVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

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
