#ifndef __VLOG_DM_VARIABLE_TYPE_IMPL_HPP__
#define __VLOG_DM_VARIABLE_TYPE_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_variable_type.hpp"

#include "vlog_data_model\ih\visitors\vlog_dm_type_visitor.hpp"

#include "vlog_data_model\sources\model\vlog_dm_type_base_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class VariableTypeImpl
	:	public TypeBaseImpl< VariableType, VariableKind >
{

/***************************************************************************/

	typedef
		TypeBaseImpl< VariableType, VariableKind >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	VariableTypeImpl(
			std::unique_ptr< Dimension > _dimension
		,	VariableKind::Kind _kind
	);

	void accept( TypeVisitor & _visitor ) const override;

/***************************************************************************/

};

/***************************************************************************/

inline
VariableTypeImpl::VariableTypeImpl(
		std::unique_ptr< Dimension > _dimension
	,	VariableKind::Kind _kind
	)
	:	BaseClass( std::move( _dimension ), _kind )
{
}

/***************************************************************************/

inline
void 
VlogDM::VariableTypeImpl::accept( TypeVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_VARIABLE_TYPE_IMPL_HPP__
