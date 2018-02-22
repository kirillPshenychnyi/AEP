#ifndef __VLOG_DM_FWD_HPP__
#define __VLOG_DM_FWD_HPP__

namespace VlogDM
{
	namespace Writable 
	{
		struct DesignUnitFactory;
		struct DeclarationFactory;
		struct DeclaredFactory;
		struct ItemsFactory;
		struct ExpressionFactory;
		struct TypeFactory;

		struct DesignUnit;
		struct PortDeclaration;
		struct VariableDeclaration;
		struct MultidimensionalRange;

		struct Concatenation;

		typedef
			std::unique_ptr< DesignUnit >
			DesignUnitPtr;

		typedef
			std::unique_ptr< PortDeclaration >
			PortDeclarationPtr;

		typedef
			std::unique_ptr< VariableDeclaration >
			VariableDeclarationPtr;

		typedef
			std::unique_ptr< MultidimensionalRange >
			MultidimensionalRangePtr;
	}

	struct IAccessor;

	struct DesignUnit;
	struct Declaration;
	struct Dimension;
	struct Type;
	struct Declared;
	struct Location;
	struct Port;
	struct Variable;
	struct Range;
	struct Process;

	struct ContinuousAssignment;

	struct BaseIdentifier;

	struct Expression;
	struct PrimaryLiteral;
	struct UnaryOperator;
	struct BinaryOperator;
	struct PrimaryIdentifier;
	struct Concatenation;

	struct DesignUnitFactory;

	typedef
		std::unique_ptr< DesignUnit >
		DesignUnitPtr;

	typedef
		std::unique_ptr< Declared >
		DeclaredPtr;

	typedef
		std::unique_ptr< Type >
		TypePtr;

	typedef
		std::unique_ptr< Dimension >
		DimensionPtr;

	typedef
		std::unique_ptr< Port >
		PortPtr;

	typedef
		std::unique_ptr< Variable >
		VariablePtr;
	
	typedef
		std::unique_ptr< Range >
		RangePtr;

	typedef
		std::unique_ptr< Expression >
		ExpressionPtr;

	typedef
		std::unique_ptr< BaseIdentifier >
		BaseIdentifierPtr;

	typedef
		std::unique_ptr< ContinuousAssignment >
		ContinuousAssignmentPtr;

	typedef
		std::unique_ptr< Process >
		ProcessPtr;
}

#endif // !__VLOG_DM_FWD_HPP__

