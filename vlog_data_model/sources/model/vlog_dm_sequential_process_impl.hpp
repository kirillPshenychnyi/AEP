#ifndef __VLOG_DM_SEQUENTIAL_PROCES__IMPL_HPP__
#define __VLOG_DM_SEQUENTIAL_PROCES__IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_sequential_process.hpp"
#include "vlog_data_model\api\vlog_dm_statement.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct SequentialProcessImpl
	:	public LocatedImpl< SequentialProcess >
{

/***************************************************************************/

	typedef
		LocatedImpl< SequentialProcess >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	SequentialProcessImpl(
			Location const & _location
		,	StatementPtr _statement
	);

/***************************************************************************/

	Statement const & getStatement() const override;

	void accept( ProcessVisitor & _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	StatementPtr m_statement;

/***************************************************************************/

};

/***************************************************************************/

SequentialProcessImpl::SequentialProcessImpl(
		Location const & _location
	,	StatementPtr _statement
	)
	:	BaseClass( _location )
	,	m_statement( std::move( _statement ) )
{
}

/***************************************************************************/

Statement const & 
SequentialProcessImpl::getStatement() const
{
	assert( m_statement );

	return *m_statement;
}

/***************************************************************************/

void 
SequentialProcessImpl::accept( ProcessVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_SEQUENTIAL_PROCES__IMPL_HPP__
