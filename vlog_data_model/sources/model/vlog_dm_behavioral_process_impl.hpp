#ifndef __VLOG_DM_BEHAVIORAL_PROCES__IMPL_HPP__
#define __VLOG_DM_BEHAVIORAL_PROCES__IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\sources\model\vlog_dm_located_impl.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"

#include "vlog_data_model\api\vlog_dm_behavioral_process.hpp"
#include "vlog_data_model\api\vlog_dm_statement.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

struct BehavioralProcessImpl
	:	public LocatedImpl< BehavioralProcess >
{

/***************************************************************************/

	typedef
		LocatedImpl< BehavioralProcess >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/

	BehavioralProcessImpl(
			Location const & _location
		,	StatementPtr _statement
		,	SensitivityListPtr _timingControl
	);

/***************************************************************************/

	Statement const & getStatement() const override;
	
	boost::optional< SensitivityList const & > getSensitivityList() const override;

	void accept( ProcessVisitor & _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	StatementPtr m_statement;
	
	SensitivityListPtr m_sensitivityList;

/***************************************************************************/

};

/***************************************************************************/

BehavioralProcessImpl::BehavioralProcessImpl(
		Location const & _location
	,	StatementPtr _statement
	,	SensitivityListPtr _sensitivityList
	)
	:	BaseClass( _location )
	,	m_statement( std::move( _statement ) )
	,	m_sensitivityList( std::move( _sensitivityList ) )
{
}

/***************************************************************************/

Statement const & 
BehavioralProcessImpl::getStatement() const
{
	assert( m_statement );

	return *m_statement;
}

/***************************************************************************/

inline 
boost::optional< SensitivityList const & >
BehavioralProcessImpl::getSensitivityList() const
{
	return Tools::Convertors::convertPointerToOptional( m_sensitivityList.get() );
}

/***************************************************************************/

void 
BehavioralProcessImpl::accept( ProcessVisitor & _visitor ) const
{
	_visitor.visit( *this );
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_BEHAVIORAL_PROCES__IMPL_HPP__
