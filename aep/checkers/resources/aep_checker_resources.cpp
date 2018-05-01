#include "stdafx.h"

#include "aep\checkers\resources\aep_checker_resources.hpp"

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

/***************************************************************************/

}

/***************************************************************************/

namespace FullCaseSynDirecriveChecker {

/***************************************************************************/

	const char CheckerInstanceName[] = "check_full_case_%1%";

	const char CheckTerm[] = "%1% == %2%";

	const char OrItem[] = " | ";

	const char CheckExpression[] = "(%1%) !== 1'b0";

	const char CheckExpressionWire[] = "test_full_case_%1%";
	
	const char FireWire[] = "fire_full_case_%1%";

	const char Message[] = "case is not full while synthesis full_case directive used";

	const char CaseSelWire[] = "case_sel_wire_line_%1%";

/***************************************************************************/

}

/***************************************************************************/

}
}

/***************************************************************************/