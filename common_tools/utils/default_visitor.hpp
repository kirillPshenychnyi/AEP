#ifndef __COMMON_TOOLS_DEFAULT_VISITOR_HPP__
#define __COMMON_TOOLS_DEFAULT_VISITOR_HPP__

/***************************************************************************/

namespace Tools {

/***************************************************************************/

// base
template < typename _BaseVisitor, typename... _Types >
struct DefaultVisitor;

// single
template < typename _BaseVisitor, typename _Type >
struct DefaultVisitor< _BaseVisitor, _Type >
	:	public _BaseVisitor
{

/***************************************************************************/

	void visit( _Type const & _type ) override
	{
	}

/***************************************************************************/

};

/***************************************************************************/

// multiple
template < typename _BaseVisitor, typename _Type, typename ... _Other >
struct DefaultVisitor< _BaseVisitor, _Type, _Other... >
	:	public DefaultVisitor< _BaseVisitor, _Other ... >
{

/***************************************************************************/

	using DefaultVisitor< _BaseVisitor, _Other ... >::visit;

	void visit( _Type const & _inst ) override {}

/***************************************************************************/

};

/***************************************************************************/

#define DECLARE_DEFAULT_VISITOR( Name, ... )				\
	typedef													\
		Tools::DefaultVisitor< Name##Visitor, __VA_ARGS__ > \
		Name##DefaultVisitor;


/***************************************************************************/

}

/***************************************************************************/

#endif // !__COMMON_TOOLS_DEFAULT_VISITOR_HPP__
