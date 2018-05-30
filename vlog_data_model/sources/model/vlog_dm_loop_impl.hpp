#ifndef __VLOG_DM_LOOP_IMPL_HPP__
#define __VLOG_DM_LOOP_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\api\vlog_dm_statement.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_statement_visitor.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

template< typename _TLoop >
class LoopImpl
	:	public LocatedImpl< _TLoop >
{

/***************************************************************************/

	typedef
		LocatedImpl< _TLoop >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	LoopImpl( Location const & _location, StatementPtr _loopStmt );

/***************************************************************************/

public:

/***************************************************************************/

	Statement const & getLoopStatement() const override;

	void accept( StatementVisitor & _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	StatementPtr m_loopStmt;

/***************************************************************************/

};

/***************************************************************************/

template< typename _TLoop >
inline 
LoopImpl< _TLoop >::LoopImpl( Location const & _location, StatementPtr _loopStmt )
	:	BaseClass( _location )
	,	m_loopStmt( std::move( _loopStmt ) )
{
}

/***************************************************************************/

template< typename _TLoop >
inline 
Statement const & 
LoopImpl< _TLoop >::getLoopStatement() const
{
	assert( m_loopStmt );
	return *m_loopStmt;
}

/***************************************************************************/

template< typename _TLoop >
inline 
void 
LoopImpl< _TLoop >::accept( StatementVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/



/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_LOOP_IMPL_HPP__
