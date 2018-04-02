#ifndef __AEP_MODEL_CHECKER_BUILDERS_UTILS_HPP__
#define __AEP_MODEL_CHECKER_BUILDERS_UTILS_HPP__

/*----------------------------------------------------------------------------*/

namespace AepModel {

/*----------------------------------------------------------------------------*/

#define AEP_DEFINE_GENERIC_SETER( NOT_USED1, NOT_USED2, TYPE )			\
void																	\
BOOST_PP_CAT( set, BOOST_PP_TUPLE_ELEM(2, 0, TYPE) )(					\
		BOOST_PP_TUPLE_ELEM(2, 1, TYPE) _value							\
)																		\
{																		\
	setGeneric< 														\
			BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,0,TYPE), Param)			\
		,	BOOST_PP_TUPLE_ELEM(2, 1, TYPE) 							\
		>(																\
			GenericType::BOOST_PP_TUPLE_ELEM(2,0,TYPE)					\
		,	_value														\
	);																	\
}

/*----------------------------------------------------------------------------*/


#define AEP_DEFINE_PORT_SETTER( NOT_USED1, NOT_USED2, NAME )		\
void																\
BOOST_PP_CAT( set, NAME ) ( std::string const & _value )			\
{																	\
	m_checker->setPort( OvlCheckerPortKind::NAME, _value );			\
}


/*----------------------------------------------------------------------------*/


#define AEP_DEFINE_PORT_AS_WIRE( NOT_USED1, NOT_USED2, NAME )					\
void																			\
BOOST_PP_CAT( set, NAME ) ( 													\
		std::string const & _lhs												\
	,	std::string const & _rhs												\
	,	int _width 																\
	)																			\
{																				\
	m_checker->setPortAsWire( OvlCheckerPortKind::NAME, _lhs, _rhs, _width );	\
}

/*----------------------------------------------------------------------------*/

#define COMMON_GENERICS	\
	( SeverityLevel )	\
	( ClockEdge )		\
	( ResetPolarity )	\
	( Msg )	

/*----------------------------------------------------------------------------*/

#define COMMON_PORTS	\
	( Fire )			\
	( Clock )			\
	( Reset ) 			\
	( Enable )

/*----------------------------------------------------------------------------*/

} 

/*----------------------------------------------------------------------------*/

#endif //!__AEP_MODEL_CHECKER_BUILDERS_UTILS_HPP__
