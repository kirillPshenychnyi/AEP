#ifndef __AEP_MODEL_ASSERTION_CONTEXT_SET_IMPL_HPP__
#define __AEP_MODEL_ASSERTION_CONTEXT_SET_IMPL_HPP__

/***************************************************************************/

#include "aep_model\api\contexsts\aep_model_assertion_contexts_set.hpp"
#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"

#include "common_tools\collections\tools_collection_utils.hpp"

#include <boost\unordered_set.hpp>

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

class AssertionContextSetImpl
	:	public AssertionContextSet
{

/***************************************************************************/

	struct ContextHasher
	{
		std::size_t operator()( AssertionContextPtr const & _context ) const
		{
			return operator()( _context->getDUTName() );
		}

		std::size_t operator()( std::string const & _dutName ) const
		{
			return boost::hash_value( _dutName );
		}
	};

	struct ContextComparator
	{
		bool operator()( 
				AssertionContextPtr const & _lhs
			,	AssertionContextPtr const & _rhs 
		) const
		{
			return operator()( _lhs->getDUTName(), _rhs );
		}

		bool operator()( 
				AssertionContextPtr const & _lhs
			,	std::string const & _rhs 
		) const
		{
			return operator()( _rhs, _lhs );
		}

		bool operator()( 
				std::string const & _lhs
			,	AssertionContextPtr const & _rhs 
		) const
		{
			return _lhs == _rhs->getDUTName();
		}
	};

	typedef
		boost::unordered_set< AssertionContextPtr, ContextHasher, ContextComparator >
		ContextSet;

/***************************************************************************/

	void addContext( AssertionContextPtr _context ) final;

	bool hasAssertionContext( std::string const & _dutName ) const final;

	void forEachAssertionContext( AssertionContextCallback _callBack ) const final;

	void forEachAssertionContext( ConstAssertionContextCallback _callBack ) final;

	boost::optional< AssertionContext & > takeContext( 
		std::string const & _dutName 
	) final;

	boost::optional< AssertionContext const & > getContext( 
		std::string const & _dutName 
	) const final;

	void clear() final;

/***************************************************************************/

private:

/***************************************************************************/

	ContextSet m_contexts;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_ASSERTION_CONTEXT_SET_IMPL_HPP__
