#ifndef __AEP_RANGE_BOUND_CHECKER_HPP__
#define __AEP_RANGE_BOUND_CHECKER_HPP__

/***************************************************************************/

#include "aep\checkers\aep_base_checker.hpp"

/***************************************************************************/

namespace Aep {

/***************************************************************************/

class RangeBoundChecker
	:	public BaseAepChecker
{

/***************************************************************************/

public:

/***************************************************************************/

	RangeBoundChecker( IAccessor & _aep );

/***************************************************************************/

	void analyze() final;

/***************************************************************************/

public:

/***************************************************************************/

	template< typename _TProcess >
	void onProcess( _TProcess const & _process );

	void checkId( VlogDM::PrimaryIdentifier const & _id );

	int getMaxBoundOfDimension( 
			int _dimension
		,	VlogDM::PrimaryIdentifier const & _id 
	);

	void registerAssertion(
			VlogDM::Expression const & _selExpression
		,	VlogDM::PrimaryIdentifier const & _id 
		,	int _maxBound
	);

	std::unique_ptr< AepModel::OvlChecker > createChecker(
			VlogDM::Expression const & _selExpression
		,	VlogDM::PrimaryIdentifier const & _id 
		,	int _maxBound
	);

/***************************************************************************/

}; 

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_RANGE_BOUND_CHECKER_HPP__
