#ifndef __AEP_MODEL_CONTEXT_REGENERATOR_HPP__
#define __AEP_MODEL_CONTEXT_REGENERATOR_HPP__

/***************************************************************************/

#include "aep_model\api\aep_model_fwd.hpp"

/***************************************************************************/

namespace AepModel { 

/***************************************************************************/

class ContextSetRegenerator
{

/***************************************************************************/

public:

/***************************************************************************/

	ContextSetRegenerator(
			AssertionContextSet const & _contextSet
		,	std::ostream & _stream 
	);

	void run();

/***************************************************************************/

private:

/***************************************************************************/

	void regenerateContext( 
			std::string const & _instanceName
		,	AssertionContext const & _context 
	);

	void regeneratePorts( AssertionContext const & _context );

	void regenerateCheckers( AssertionContext const & _context );

	void regenerateChecker( OvlChecker const & _checker );

	void regenerateInstances( AssertionContext const & _context );

	void regenerateInstance( 
			AssertionContext const & _context
		,	std::string const & _instance
	);

	void regenerateTopLevel();

	template< typename _ParamKind >
	void regenerateAssignmentParam(
			int _nTotal
		,	int & _currentItem
		,	_ParamKind const & _item
		,	std::function< std::string ( _ParamKind const & ) > nameGetter
		,	std::function< std::string ( _ParamKind const & ) > _valueGetter
	);

	template< typename ... _Args >
	void regeneratSignal(
			std::string const & _scalarPattern
		,	std::string const & _vectorPattern
		,	int _width
		,	_Args ... _params
	);

/***************************************************************************/

private:

/***************************************************************************/

	AssertionContextSet const & m_contextSet;
	
	std::ostream & m_targetStream;

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_CONTEXT_REGENERATOR_HPP__
