#ifndef __VLOG_DM_NAMED_LOCATED_IMPL_HPP__
#define __VLOG_DM_NAMED_LOCATED_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_named_impl.hpp"
#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_named.hpp"

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/

template < typename _Base >
class NamedLocatedImpl
	:	public NamedImpl< _Base >
{

/***************************************************************************/

	typedef
		NamedImpl< _Base >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	NamedLocatedImpl(
		  std::string const & _name
		, Location const & _location 
	);

/***************************************************************************/

	Location const & getLocation() const override;

/***************************************************************************/

private:

/***************************************************************************/

	Location m_location;

/***************************************************************************/

};

/***************************************************************************/

template< typename _Base >
NamedLocatedImpl< _Base >::NamedLocatedImpl(
		std::string const & _name
	,	Location const & _location
	)
	:	m_location( _location )
	,	BaseClass( _name )
{
}

/***************************************************************************/

template< typename _Base >
inline
Location const & 
NamedLocatedImpl< _Base >::getLocation() const
{
	return m_location;
}

/***************************************************************************/

}

#endif // !__VLOG_DM_NAMED_LOCATED_IMPL_HPP__
