#ifndef __EC_ERRORS_SET_IMPL_HPP__
#define __EC_ERRORS_SET_IMPL_HPP__

/***************************************************************************/

#include "entry_controller\api\errors\ec_iimport_errors_set.hpp"
#include "entry_controller\api\errors\ec_ibase_import_error.hpp"

#include "common_tools\collections\tools_ordered_mapping.hpp"

/***************************************************************************/

namespace EntryController {
namespace Errors {

/***************************************************************************/

class ErrorsSet
	:	public IImportErrorsSet
{

/***************************************************************************/

	struct Hasher
	{
		std::size_t operator() ( const ImportError * const _error ) const
		{
			return _error->hash();
		}
	};

	struct Comparator
	{
		bool operator() ( 
				const ImportError * const _lhs
			,	const ImportError * const _rhs 
		) const
		{
			return _lhs->isEqualTo( *_rhs );
		}
	};

	typedef
		Tools::Collections::OrderedSet< 
				ImportError *
			,	Hasher
			,	Comparator 
			,	std::default_delete< ImportError >
		>
		Errors;

/***************************************************************************/

public:

/***************************************************************************/

	~ErrorsSet() = default;

	void addError( ErrorPtr _error ) final;

	void forEachError( ErrorCallback _callback ) const final;

	bool hasErrors() const;

	int getErrorsCount() const;

	ImportError const & getError ( int _idx ) const;

/***************************************************************************/

private:

/***************************************************************************/

	Errors m_errors;

/***************************************************************************/

};

/***************************************************************************/

inline 
int 
ErrorsSet::getErrorsCount() const
{
	return m_errors.size();
}

/***************************************************************************/

inline 
ImportError const & 
ErrorsSet::getError( int _idx ) const
{
	return *m_errors[ _idx ];
}

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_ERRORS_SET_IMPL_HPP__
