#include "stdafx.h"

#include "aep\sources\checkers\resources\aep_checker_resources.hpp"

/***************************************************************************/

namespace Aep {
namespace Resources {

/***************************************************************************/

namespace CommonValues {

/***************************************************************************/

	const char Enable[] = "1'b1";

	const char Reset[] = "1'b1";

/***************************************************************************/

}

/***************************************************************************/

namespace Separators {

/***************************************************************************/

	const char ParenthesesOpen[] = "( ";

	const char ParenthesesClose[] = " )";

	const char Space = ' ';

	const char Coma[] = ", ";

/***************************************************************************/

}

/***************************************************************************/

namespace FullCaseSynDirecriveChecker {

/***************************************************************************/

	const char CheckerInstanceName[] = "check_full_case_%1%";

	const char CheckTerm[] = "%1% == %2%";

	const char OrItem[] = " | ";

	const char CheckExpression[] = "%1% !== 1'b0";

	const char CheckExpressionWire[] = "test_full_case_%1%";
	
	const char FireWire[] = "fire_full_case_%1%";

	const char Message[] = "case is not full while synthesis full_case directive used";

	const char CaseSelWire[] = "case_sel_wire_line_%1%";

/***************************************************************************/

}

/***************************************************************************/

namespace ParallelCaseSynDirecriveChecker {

/***************************************************************************/

	const char CheckerInstanceName[] = "check_parallel_case_%1%";

	const char CheckTerm[] = "( %1% == %2% ) !== 1'b0";

	const char CheckExpression[] = "{%1%}";

	const char CheckExpressionWire[] = "test_parallel_case_%1%";
	
	const char FireWire[] = "fire_parallel_case_%1%";

	const char Message[] = "case is not parallel while synthesis parallel_case directive used";

	const char CaseSelWire[] = "case_sel_wire_line_%1%";

/***************************************************************************/

}

/***************************************************************************/

namespace RangeBoundChecker {

/***************************************************************************/

	const char CheckExpression[] = "%1% < %2%";
	
	const char CheckExpressionWire[] = "test_overflow_%1%";

	const char CheckerInstanceName[] = "check_overflow_%1%";

	const char FireWire[] = "fire_range_overflow_%1%";
	
	const char Message[] = "boundary overflow of an \\\"%1%\\\" bus at %2%, %3%" ;

/***************************************************************************/

}

/***************************************************************************/

}
}

/***************************************************************************/