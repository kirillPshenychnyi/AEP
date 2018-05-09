#ifndef __TOOLS_VISITOR_CAST_HPP__
#define __TOOLS_VISITOR_CAST_HPP__

/*----------------------------------------------------------------------------*/

namespace Tools {

/*----------------------------------------------------------------------------*/

template< typename _Type >
struct ConstTraits
{
	typedef const _Type& ResultType;
};

/*----------------------------------------------------------------------------*/

template< typename _Type >
struct NonConstTraits
{
	typedef _Type& ResultType;
};

/*----------------------------------------------------------------------------*/

template<
		typename _TargetType
	,	typename _SourceRootType
	,	typename _DefaultVisitor
	,	template< typename > class _Traits = ConstTraits
>
class Cast
	:	private _DefaultVisitor
{

/*----------------------------------------------------------------------------*/

public:

/*----------------------------------------------------------------------------*/

	typedef typename _Traits< _TargetType >::ResultType TargetType;

	typedef typename _Traits< _SourceRootType >::ResultType SourceRootType;

/*----------------------------------------------------------------------------*/

	boost::optional< TargetType > cast ( SourceRootType _sourceObject )
	{
		m_castResult.reset();
		_sourceObject.accept( *this );
		return m_castResult;
	}

/*----------------------------------------------------------------------------*/

private:

/*----------------------------------------------------------------------------*/

	void visit ( TargetType _targetObject ) final
	{
		m_castResult = _targetObject;
	}

/*----------------------------------------------------------------------------*/

	boost::optional< TargetType > m_castResult;

/*----------------------------------------------------------------------------*/

};

/*----------------------------------------------------------------------------*/

#define DEFINE_CAST( _construct )											\
template< typename _TargetType >											\
class _construct##Cast														\
	:	public Tools::Cast< _TargetType, _construct, _construct##DefaultVisitor >	\
{																			\
};																			\

/***************************************************************************/

} 

/*----------------------------------------------------------------------------*/

#endif //__TOOLS_VISITOR_CAST_HPP__
