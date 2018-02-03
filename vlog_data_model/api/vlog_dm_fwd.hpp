#ifndef __VLOG_DM_FWD_HPP__
#define __VLOG_DM_FWD_HPP__

namespace VlogDM
{
	namespace Writable 
	{
		struct DesignUnit;
		struct PortDeclaration;
		struct VariableDeclaration;

		typedef
			std::unique_ptr< PortDeclaration >
			PortDeclarationPtr;

		typedef
			std::unique_ptr< VariableDeclaration >
			VariableDeclarationPtr;
	}

	struct DesignUnit;
	struct Declaration;
	struct Dimension;
	struct Type;
	struct Declared;
	struct Location;
	struct Port;
	struct Variable;

	struct DesignUnitFactory;

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
}

#endif // !__VLOG_DM_FWD_HPP__

