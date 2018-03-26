#ifndef __VLOG_DM_DECLARATION_IMPL_HPP__
#define __VLOG_DM_DECLARATION_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_declaration.hpp"
#include "vlog_data_model\api\vlog_dm_declared.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_type.hpp"

#include "sources\model\vlog_dm_located_impl.hpp"

#include "common_tools\collections\tools_collection_utils.hpp"

#include <boost\unordered_set.hpp>

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
		Tools::Collections::NamedHasher< DeclaredPtr >
		DeclaredHasher;

	typedef
		Tools::Collections::NamedComparator< DeclaredPtr >
		DeclaredComparator;

	typedef
		boost::unordered_set< DeclaredPtr, DeclaredHasher, DeclaredComparator >
		Declareds;

/***************************************************************************/

public:

/***************************************************************************/

	DeclarationImpl( Location const & _location, TypePtr _type );

/***************************************************************************/

	boost::optional< Declared const & > findDeclared( 
		std::string const & _declared 
	) const final;

	Type const & getType() const final;

	int getDeclaredsCount() const final;

/***************************************************************************/

protected:

/***************************************************************************/

	void addDeclared( DeclaredPtr _declared ) final;

/***************************************************************************/

private:

/***************************************************************************/

	Declareds m_declareds;

	TypePtr m_type;

/***************************************************************************/

};

/***************************************************************************/

template< typename _Writable >
DeclarationImpl< _Writable >::DeclarationImpl(
		Location const & _location
	,	std::unique_ptr< Type > _type
	)	
	:	BaseClass( _location )
	,	m_type( std::move( _type ) )
{
}

/***************************************************************************/

template< typename _Writable >
boost::optional< Declared const & > 
DeclarationImpl< _Writable >::findDeclared( std::string const & _declared ) const 
{
	auto value = m_declareds.find( _declared, DeclaredHasher(), DeclaredComparator() );

	return
			value == m_declareds.end()
		?	boost::optional< Declared const & >()
		:	**value;

}

/***************************************************************************/

template< typename _Writable >
inline Type const & 
DeclarationImpl< _Writable >::getType() const
{
	return *m_type;
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
	m_declareds.insert( std::move( _declared ) );
}

/***************************************************************************/

}

#endif // __VLOG_DM_DECLARATION_IMPL_HPP__