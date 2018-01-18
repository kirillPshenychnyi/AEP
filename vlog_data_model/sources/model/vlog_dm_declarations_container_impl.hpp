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

	void addDeclaration( std::unique_ptr< Declaration > _declaration ) override;

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

}

/***************************************************************************/

#endif // !__VLOG_DM_DECLARATIONS_CONTAINER_IMPL_HPP__
