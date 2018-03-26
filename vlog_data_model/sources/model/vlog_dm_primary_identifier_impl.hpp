#ifndef __VLOG_DM_PRIMARY_IDENTIFIER_IMPL_HPP__
#define __VLOG_DM_PRIMARY_IDENTIFIER_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_expression_visitor.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class PrimaryIdentifierImpl
	:	public LocatedImpl< PrimaryIdentifier >
{

/***************************************************************************/

	typedef
		LocatedImpl< PrimaryIdentifier >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	PrimaryIdentifierImpl(
			Location const & _location
		,	BaseIdentifierPtr _identifier
	);

/***************************************************************************/

public:

/***************************************************************************/

	BaseIdentifier const & getIdentifier() const final;

	void accept( ExpressionVisitor & _visitor ) const final;

/***************************************************************************/

private:

/***************************************************************************/

	BaseIdentifierPtr m_identifier;

/***************************************************************************/

};

/***************************************************************************/

PrimaryIdentifierImpl::PrimaryIdentifierImpl(
		Location const & _location
	,	BaseIdentifierPtr _identifier
	)
	:	BaseClass( _location )
	,	m_identifier( _identifier.release() )
{
}

/***************************************************************************/

BaseIdentifier const & 
PrimaryIdentifierImpl::getIdentifier() const
{
	return *m_identifier;
}

/***************************************************************************/

void 
PrimaryIdentifierImpl::accept( ExpressionVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_PRIMARY_IDENTIFIER_IMPL_HPP__
