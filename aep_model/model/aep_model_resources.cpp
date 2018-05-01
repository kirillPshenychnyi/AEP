#include "stdafx.h"

#include "aep_model\model\aep_model_resources.hpp"

/***************************************************************************/

namespace AepModel {
namespace Resources { 

/***************************************************************************/

namespace Strings {

/***************************************************************************/

	const char Header[] = "`include \"std_ovl_defines.h\"";

	const char AepModuleName[] = "%1%_%2%_aep";

	const char TopAepModuleName[] = "top_aep";

/***************************************************************************/

}

/***************************************************************************/

namespace Separators {

/***************************************************************************/

	const char Coma[] = ", ";

	const char Tab = '\t';

	const char OpenParentheses[] = "( ";
	const char CloseParentheses[] = " )";
	const char Semicolon = ';';
	
/***************************************************************************/

}

/***************************************************************************/

namespace HdlPatterns {

/***************************************************************************/

	const char ModuleDeclaration[] = "module %1%";

	const char WireDeclaration[] = "input wire %1%;";

	const char VectorDeclaration[] = "input wire [%1%:%2%] %3%;";

	const char AssignedWireDeclaration[] = "wire %1% = %2%;";

	const char AssignedVectorDeclaration[] = "wire [%1%:%2%] %3% = %4%;";

	const char AssignmentPattern[] = ".%1%( %2% )";

	const char Endmodule[] = "endmodule // %1%";

	const char BeginInstantiation[] = "%1% %2%(";

	const char InnerSignalRefererence[] = "`DUT.%1%.%2%";

/***************************************************************************/

}

/***************************************************************************/

}
}