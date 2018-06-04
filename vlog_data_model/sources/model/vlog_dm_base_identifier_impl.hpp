#ifndef __VLOG_DM_BASE_IDENTIFIER_IMPL_HPP__
#define __VLOG_DM_BASE_IDENTIFIER_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_declared.hpp"
#include "vlog_data_model\api\vlog_dm_range.hpp"

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class BaseIdentifierImplBase
	:	public LocatedImpl< BaseIdentifier >
{
	
/***************************************************************************/

	typedef
		LocatedImpl< BaseIdentifier >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	BaseIdentifierImplBase(
			Location const & _location
		,	Declared const & _declared
	);

	virtual ~BaseIdentifierImplBase() = default;

/***************************************************************************/

public:

/***************************************************************************/

	Declared const & getDeclared() const final;

	boost::optional< Range const & > getRange() const override;

	std::string const& getName() const final;

/***************************************************************************/

private:

/***************************************************************************/

	Declared const & m_declared;

/***************************************************************************/

};

/***************************************************************************/

BaseIdentifierImplBase::BaseIdentifierImplBase(
		Location const & _location
	,	Declared const & _declared
	)
	:	BaseClass( _location )
	,	m_declared( _declared )
{
}

/***************************************************************************/

Declared const & 
BaseIdentifierImplBase::getDeclared() const
{
	return m_declared;
}

/***************************************************************************/

std::string const& 
BaseIdentifierImplBase::getName() const
{
	return m_declared.getName();
}

/***************************************************************************/

boost::optional< Range const & > 
BaseIdentifierImplBase::getRange() const
{
	return boost::none;
}

/***************************************************************************/

template< bool _HasRange >
class BaseIdentifierImpl;

/***************************************************************************/

template<>
class BaseIdentifierImpl< false >
	:	public BaseIdentifierImplBase
{

/***************************************************************************/

public:

/***************************************************************************/

	using BaseIdentifierImplBase::BaseIdentifierImplBase;

/***************************************************************************/

};

/***************************************************************************/

template<>
class BaseIdentifierImpl< true >
	:	public BaseIdentifierImplBase
{

/***************************************************************************/

public:

/***************************************************************************/

	BaseIdentifierImpl(
			Location const & _location
		,	Declared const & _declared
		,	RangePtr _range
		)
		:	BaseIdentifierImplBase( _location, _declared )
		,	m_range( _range.release() )
	{}

/***************************************************************************/

	boost::optional< Range const & > getRange() const override
	{
		return *m_range;
	}

/***************************************************************************/

private:

/***************************************************************************/

	RangePtr m_range;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_BASE_IDENTIFIER_IMPL_HPP__
