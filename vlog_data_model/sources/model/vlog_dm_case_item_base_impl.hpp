#ifndef __VLOG_DM_CASE_ITEM_BASE_IMPL_HPP__
#define __VLOG_DM_CASE_ITEM_BASE_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\api\vlog_dm_statement.hpp"

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

	void setStatement( StatementPtr _statement ) override;

	Statement const & getStatement() const override;

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

}

/***************************************************************************/

#endif // !__VLOG_DM_CASE_ITEM_BASE_IMPL_HPP__
