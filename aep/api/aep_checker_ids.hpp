#ifndef __AEP_CHECKER_IDS_HPP__
#define __AEP_CHECKER_IDS_HPP__

/***************************************************************************/

namespace Aep {

/***************************************************************************/

enum class CheckerIds
{

/***************************************************************************/

		ParallelCaseSynDirectiveChecker = 1 << 0
	,	FullCaseSynDirectiveChecker = 1 << 1
	,	RangeBoundChecker = 1 << 2

	,	All = 
				ParallelCaseSynDirectiveChecker 
			|	FullCaseSynDirectiveChecker
			|	RangeBoundChecker

/***************************************************************************/

};
	
/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_CHECKER_IDS_HPP__
