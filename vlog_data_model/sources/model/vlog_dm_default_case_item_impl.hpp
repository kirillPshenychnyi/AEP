#ifndef __VLOG_DM_DEFAULT_CASE_ITEM_IMPL_HPP__
#define __VLOG_DM_DEFAULT_CASE_ITEM_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_case_item_base_impl.hpp"

#include "vlog_data_model\ih\writable\vlog_dm_case_item.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class DefaultCaseItemImpl
	:	public CaseItemBaseImpl< Writable::DefaultCaseItem >
{

/***************************************************************************/

	typedef
		CaseItemBaseImpl< Writable::DefaultCaseItem >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	DefaultCaseItemImpl( Location const & _location );

	bool isDefault() const override;

/***************************************************************************/

};

/***************************************************************************/

DefaultCaseItemImpl::DefaultCaseItemImpl( Location const & _location )
	:	BaseClass( _location )
{
}

/***************************************************************************/

inline
bool DefaultCaseItemImpl::isDefault() const
{
	return true;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_DEFAULT_CASE_ITEM_IMPL_HPP__
