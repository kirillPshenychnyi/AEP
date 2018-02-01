#ifndef __VLOG_DM_FWD_HPP__
#define __VLOG_DM_FWD_HPP__

namespace VlogDM
{
	namespace Writable 
	{
		struct DesignUnit;
	}

	struct Dimension;
	struct Type;
	struct Declared;

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
}

#endif // !__VLOG_DM_FWD_HPP__

