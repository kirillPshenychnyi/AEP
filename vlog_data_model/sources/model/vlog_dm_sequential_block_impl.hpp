#ifndef __VLOG_DM_SEQUENTIAL_BLOCK_IMPL_HPP__
#define __VLOG_DM_SEQUENTIAL_BLOCK_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_sequential_block.hpp"

#include <vector>

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class SequentialBlockImpl
	:	public LocatedImpl< Writable::SequentialBlock >
{

/***************************************************************************/

	typedef
		std::vector< StatementPtr >
		Statements;

	typedef
		LocatedImpl< Writable::SequentialBlock >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	SequentialBlockImpl( Location const & _location );

/***************************************************************************/

	Statement const & getStatement( int _idx ) const final;

	int getStatementsCount() const final;

	void addStatement( VlogDM::StatementPtr _stmt ) final;

	void accept( StatementVisitor & _visitor ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	Statements m_statements;

/***************************************************************************/

};

/***************************************************************************/

inline
SequentialBlockImpl::SequentialBlockImpl( Location const & _location )
	:	BaseClass( _location )
{
}

/***************************************************************************/

inline
Statement const & 
SequentialBlockImpl::getStatement( int _idx ) const
{
	return *m_statements[ _idx ];
}

/***************************************************************************/

inline
int
SequentialBlockImpl::getStatementsCount() const
{
	return m_statements.size();
}

/***************************************************************************/

inline 
void
SequentialBlockImpl::addStatement( VlogDM::StatementPtr _stmt )
{
	m_statements.push_back( std::move( _stmt ) );
}

/***************************************************************************/

inline 
void SequentialBlockImpl::accept( StatementVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_SEQUENTIAL_BLOCK_IMPL_HPP__
