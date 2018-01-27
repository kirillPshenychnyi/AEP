#ifndef __VLOG_DM_NET_TYPE_IMPL_HPP__
#define __VLOG_DM_NET_TYPE_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_net_type.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_type_visitor.hpp"

#include "vlog_data_model\sources\model\vlog_dm_type_base_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class NetTypeImpl
	:	public TypeBaseImpl< NetType, NetKind >
{

/***************************************************************************/

	typedef
		TypeBaseImpl< NetType, NetKind >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	NetTypeImpl(
			std::unique_ptr< Dimension > _dimension
		,	NetKind::Kind _kind
	);

	void accept( TypeVisitor & _visitor ) const override;

/***************************************************************************/

};

/***************************************************************************/

inline 
NetTypeImpl::NetTypeImpl( 
		std::unique_ptr< Dimension > _dimension
	,	NetKind::Kind _kind 
	)
	:	BaseClass( std::move( _dimension ), _kind )
{
}

/***************************************************************************/

inline 
void NetTypeImpl::accept( TypeVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_NET_TYPE_IMPL_HPP__
