#ifndef __VLOG_DM_DECLARED_IMPL_HPP__
#define __VLOG_DM_DECLARED_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_declared.hpp"
#include "vlog_data_model\api\vlog_dm_type.hpp"
#include "vlog_data_model\sources\model\vlog_dm_named_located_impl.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

template < typename _Base >
class DeclaredImpl
	:	public NamedLocatedImpl< _Base >
{ 

/***************************************************************************/

	typedef
		NamedLocatedImpl< _Base >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	DeclaredImpl(
			Declaration const & _declaration
		,	std::unique_ptr< Type > _type
		,	std::string const & _name
		,	Location const & _location
	);

/***************************************************************************/

	Declaration const & getDeclaration() const override;
	
	Type const & getType() const override;

/***************************************************************************/

private:

/***************************************************************************/

	Declaration const & m_declaration;
	std::unique_ptr< Type > m_type;

/***************************************************************************/

};

/***************************************************************************/

template< typename _BaseClass >
inline
Declaration const & 
DeclaredImpl< _BaseClass >::getDeclaration() const
{
	return m_declaration;
}

/***************************************************************************/

template< typename _BaseClass >
inline
Type const & 
DeclaredImpl< _BaseClass >::getType() const
{
	return *m_type;
}

/***************************************************************************/

template< typename _BaseClass >
inline
DeclaredImpl< _BaseClass >::DeclaredImpl( 
		Declaration const & _declaration
	,	std::unique_ptr< Type > _type
	,	std::string const & _name
	,	Location const & _location
)
	:	BaseClass( _name, _location )
	,	m_declaration( _declaration )
	,	m_type( _type.release() )
{
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DECLARED_IMPL_HPP__
