#ifndef __VLOG_DM_DECLARATIONS_CONTAINER_IMPL_HPP__
#define __VLOG_DM_DECLARATIONS_CONTAINER_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_declaration.hpp"

#include <vector>

/***************************************************************************/

namespace VlogDM{

/***************************************************************************/

template< typename _BaseClass >
class DeclarationsContainerImpl
	:	public _BaseClass
{

/***************************************************************************/

	typedef
		std::vector< std::unique_ptr< Declaration > >
		Declarations;

/***************************************************************************/

public:

/***************************************************************************/

	void addDeclaration( std::unique_ptr< Declaration > _declaration ) final;

	int getDeclarationsCount() const final;

	Declaration const& getDeclaration( int _idx ) const final;

	boost::optional< Declared const& > findDeclared( 
			std::string const & _declared 
	) const final;

/***************************************************************************/

private:

/***************************************************************************/

	Declarations m_declarations;

/***************************************************************************/

};

/***************************************************************************/

template<typename _BaseClass>
inline
void 
DeclarationsContainerImpl< _BaseClass >::addDeclaration(
		std::unique_ptr< Declaration > _declaration
	)
{
	m_declarations.push_back( std::move( _declaration ) );
}

/***************************************************************************/

template< typename _BaseClass >
inline 
int 
DeclarationsContainerImpl< _BaseClass >::getDeclarationsCount() const
{
	return m_declarations.size();
}

/***************************************************************************/

template< typename _BaseClass >
inline 
Declaration const& 
DeclarationsContainerImpl< _BaseClass >::getDeclaration( int _idx ) const
{
	return *m_declarations.at( _idx );
}

/***************************************************************************/

template< typename _BaseClass >
inline 
boost::optional< Declared const& >
DeclarationsContainerImpl< _BaseClass >::findDeclared( std::string const & _declared ) const
{
	for( auto const& declaration : m_declarations )
		if( auto declared = declaration->findDeclared( _declared ) )
			return declared;

	return boost::optional< Declared const& >();
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DECLARATIONS_CONTAINER_IMPL_HPP__
