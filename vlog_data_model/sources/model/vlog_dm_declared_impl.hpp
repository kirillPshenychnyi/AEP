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
		,	std::string const & _name
		,	Location const & _location
	);

/***************************************************************************/

	Declaration const & getDeclaration() const final;
	
/***************************************************************************/

private:

/***************************************************************************/

	Declaration const & m_declaration;
	
/***************************************************************************/

};

/***************************************************************************/

template< typename _BaseClass >
inline
DeclaredImpl< _BaseClass >::DeclaredImpl( 
		Declaration const & _declaration
	,	std::string const & _name
	,	Location const & _location
)
	:	BaseClass( _name, _location )
	,	m_declaration( _declaration )
{
}

/***************************************************************************/

template< typename _BaseClass >
inline
Declaration const & 
DeclaredImpl< _BaseClass >::getDeclaration() const
{
	return m_declaration;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DECLARED_IMPL_HPP__
