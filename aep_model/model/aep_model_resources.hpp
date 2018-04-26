#ifndef __AEP_MODEL_RESOURCES_HPP__
#define __AEP_MODEL_RESOURCES_HPP__

/***************************************************************************/

namespace AepModel {
namespace Resources { 

/***************************************************************************/

namespace Strings {

/***************************************************************************/

	extern const char Header[];
	extern const char AepModuleName[];
	extern const char TopAepModuleName[];

/***************************************************************************/

}

/***************************************************************************/

namespace Separators {

/***************************************************************************/

	extern const char Coma[];

	extern const char OpenParentheses[];
	extern const char CloseParentheses[];
	extern const char Semicolon;

	extern const char Tab;

/***************************************************************************/

}

/***************************************************************************/

namespace HdlPatterns {

/***************************************************************************/

	extern const char ModuleDeclaration[];

	extern const char WireDeclaration[];

	extern const char VectorDeclaration[];

	extern const char AssignedWireDeclaration[];

	extern const char AssignedVectorDeclaration[];

	extern const char AssignmentPattern[];

	extern const char BeginInstantiation[];

	extern const char Endmodule[];

	extern const char InnerSignalRefererence[];

/***************************************************************************/

}

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__AEP_MODEL_RESOURCES_HPP__
