#ifndef __VLOG_DM_DECLARATION_IMPL_HPP__
#define __VLOG_DM_DECLARATION_IMPL_HPP__

/***************************************************************************/

#include "api\vlog_dm_declaration.hpp"
#include "api\vlog_dm_declared.hpp"
#include "api\vlog_dm_location.hpp"

#include "sources\model\vlog_dm_located_impl.hpp"

#include "common_tools\collections\tools_ordered_mapping.hpp"

/***************************************************************************/

namespace VlogDM { 

/***************************************************************************/

template< typename _Writable >
class DeclarationImpl
	:	public LocatedImpl< _Writable >
{

/***************************************************************************/

	typedef
		LocatedImpl< _Writable >
		BaseClass;

	typedef
		std::shared_ptr< Declared >
		DeclaredPtr;

	typedef
		Tools::Collections::OrderedMapping< std::string, std::shared_ptr< Declared > >
		Declareds;

/***************************************************************************/

public:

/***************************************************************************/

	DeclarationImpl( Location const & _location );

/***************************************************************************/

	boost::optional< Declared const & > findDeclared( std::string const & _declared ) const override;

	int getDeclaredsCount() const override;

/***************************************************************************/

protected:

/***************************************************************************/

	void addDeclared( std::unique_ptr< Declared > _declared ) override;

/***************************************************************************/

private:

/***************************************************************************/

	Declareds m_declareds;

/***************************************************************************/

};

/***************************************************************************/

template< typename _Writable >
DeclarationImpl< _Writable >::DeclarationImpl( Location const & _location )	
	:	BaseClass( _location )
{
}

/***************************************************************************/

template< typename _Writable >
boost::optional< Declared const & > 
DeclarationImpl< _Writable >::findDeclared( std::string const & _declared ) const 
{
	auto value = m_declareds.findByKey( _declared );

	return
		value == m_declareds.asMap().end()
		?	*value->second
		:	boost::optional< Declared const & >();

}

/***************************************************************************/

template< typename _Writable >
int 
DeclarationImpl< _Writable >::getDeclaredsCount() const
{
	return m_declareds.size();
}

/***************************************************************************/

template< typename _Writable >
void 
DeclarationImpl< _Writable >::addDeclared( std::unique_ptr< Declared > _declared )
{
	m_declareds.add(
			_declared->getName()
		,	 std::shared_ptr< Declared >( _declared.release() )
	);
}

/***************************************************************************/

}

#endif // __VLOG_DM_DECLARATION_IMPL_HPP__