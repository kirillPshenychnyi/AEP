#ifndef __VLOG_DM_FWD_HPP__
#define __VLOG_DM_FWD_HPP__

namespace VlogDM
{
	namespace Writable 
	{
		struct ObjectFactory;
		struct DesignUnitFactory;
		struct DeclarationFactory;
		struct DeclaredFactory;
		struct ItemsFactory;
		struct ExpressionFactory;
		struct TypeFactory;
		struct StatementFactory;

		struct DesignUnit;
		struct PortDeclaration;
		struct VariableDeclaration;
		struct MultidimensionalRange;

		struct Concatenation;
		struct ConditionalStatement;
		struct SequentialBlock;

		struct CaseStatement;
		struct CaseItem;
		struct DefaultCaseItem;

		struct SensitivityList;

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

		typedef
			std::unique_ptr< ConditionalStatement >
			ConditionalStatementPtr;

		typedef
			std::unique_ptr< SensitivityList >
			SensitivityListPtr;

		typedef
			std::unique_ptr< CaseItem >
			CaseItemPtr;

		typedef
			std::unique_ptr< CaseStatement >
			CaseStatementPtr;

		typedef
			std::unique_ptr< DefaultCaseItem >
			DefaultCaseItemPtr;
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

	struct Statement;
	struct CaseStatement;
	struct ConditionalBranch;
	struct BlockingAssignment;

	struct ContinuousAssignment;
	struct BehavioralProcess;

	struct BaseIdentifier;

	struct Expression;
	struct PrimaryLiteral;
	struct UnaryOperator;
	struct BinaryOperator;
	struct PrimaryIdentifier;
	struct Concatenation;
	struct MultipleConcatenation;
	struct ConditionalExpression;
	struct SensitivityList;

	struct DesignUnitFactory;

	struct BaseCaseItem;
	struct CaseItem;
	struct DefaultCaseItem;

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
		std::unique_ptr< Concatenation >
		ConcatPtr;

	typedef
		std::unique_ptr< BaseIdentifier >
		BaseIdentifierPtr;

	typedef
		std::unique_ptr< ContinuousAssignment >
		ContinuousAssignmentPtr;

	typedef
		std::unique_ptr< BehavioralProcess >
		BehavioralProcessPtr;

	typedef
		std::unique_ptr< Process >
		ProcessPtr;

	typedef
		std::unique_ptr< Statement >
		StatementPtr;

	typedef
		std::unique_ptr< ConditionalBranch >
		ConditionalBranchPtr;

	typedef
		std::unique_ptr< SensitivityList >
		SensitivityListPtr;

	typedef
		std::unique_ptr< BaseCaseItem >
		BaseCaseItemPtr;

	typedef
		std::unique_ptr< CaseItem >
		CaseItemPtr;

	typedef
		std::unique_ptr< DefaultCaseItem >
		DefaultCaseItemPtr;
}

#endif // !__VLOG_DM_FWD_HPP__

