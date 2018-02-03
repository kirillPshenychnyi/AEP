#ifndef __VLOG_DM_VARIABLE_IMPL_HPP__
#define __VLOG_DM_VARIABLE_IMPL_HPP__

/***************************************************************************/

#include "vlog_data_model\api\vlog_dm_variable.hpp"

#include "vlog_data_model\sources\model\vlog_dm_dimensional_object_impl.hpp"

/***************************************************************************/

namespace VlogDM {

/***************************************************************************/

class VariableImpl
	:	public DimensionalObjectImpl< Variable >
{ 

/***************************************************************************/

	typedef
		DimensionalObjectImpl< Variable >
		BaseClass;

/***************************************************************************/

public:

/***************************************************************************/
	
	VariableImpl( 
			Declaration const & _declaration
		,	std::unique_ptr< Type > _type
		,	std::string const & _name
		,	Location const & _location
		,	std::unique_ptr< Dimension > _dimension
		,	bool _isSigned
	);

/***************************************************************************/

private:

/***************************************************************************/

	bool isSigned() const override;

	void accept( DeclaredVisitor& _visitor ) const override;

/***************************************************************************/

private:

/***************************************************************************/

	const bool m_isSigned;

/***************************************************************************/

};

/***************************************************************************/

inline
bool
VariableImpl::isSigned() const
{
	return m_isSigned;
}

/***************************************************************************/

}

/***************************************************************************/

#endif // !__VLOG_DM_VARIABLE_IMPL_HPP__
