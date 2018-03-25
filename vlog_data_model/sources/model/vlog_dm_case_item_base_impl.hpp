#ifndef __VLOG_DM_CASE_ITEM_BASE_IMPL_HPP__
#define __VLOG_DM_CASE_ITEM_BASE_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\api\vlog_dm_statement.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_case_item_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

template< typename _TBase > 
class CaseItemBaseImpl
	:	public LocatedImpl< _TBase >
{

/***************************************************************************/

	typedef
		LocatedImpl< _TBase >
		BaseClass;

/***************************************************************************/

protected:

/***************************************************************************/

	CaseItemBaseImpl( Location const & _location );

/***************************************************************************/

	void setStatement( StatementPtr _statement ) final;

	Statement const & getStatement() const final;

	void accept( CaseItemVisitor & _item ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	StatementPtr m_statement;

/***************************************************************************/

};

/***************************************************************************/

template< typename _TBase >
inline 
CaseItemBaseImpl< _TBase >::CaseItemBaseImpl( Location const & _location )
	:	BaseClass( _location )
{
}

/***************************************************************************/

template< typename _TBase >
inline
void
CaseItemBaseImpl< _TBase >::setStatement( StatementPtr _statement )
{
	assert( !m_statement );

	m_statement = std::move( _statement );
}

/***************************************************************************/

template< typename _TBase >
inline
Statement const & 
CaseItemBaseImpl< _TBase >::getStatement() const
{
	assert( m_statement );

	return *m_statement;
}

/***************************************************************************/

template< typename _TBase >
inline 
void 
CaseItemBaseImpl< _TBase >::accept( CaseItemVisitor & _item ) const
{
	_item.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_ITEM_BASE_IMPL_HPP__
