#ifndef __AEP_MODEL_CHECKER_BUILDERS_UTILS_HPP__
#define __AEP_MODEL_CHECKER_BUILDERS_UTILS_HPP__

/*----------------------------------------------------------------------------*/

namespace AepModel {

/*----------------------------------------------------------------------------*/

#define AEP_DEFINE_PORT_SETTER( PORT_NAME )									\
	void set##PORT_NAME( std::string const & _port ) final					\
	{																		\
		m_checker->setPort( OvlCheckerPortKind::Kind::PORT_NAME, _port );	\
	}

#define AEP_DEFINE_GENERIC_SETTER( KIND, GENERIC_NAME, VALUE )	\
	void set##GENERIC_NAME( VALUE _value ) final				\
	{															\
		setGeneric< Ovl##KIND##Parameter >(						\
					GenericType::Kind::GENERIC_NAME				\
				,	 _value										\
		);														\
	}

#define AEP_DEFINE_ENUM_PARAM_SETTER( GENERIC_NAME )			\
	AEP_DEFINE_GENERIC_SETTER( GENERIC_NAME, GENERIC_NAME, GENERIC_NAME::Kind )


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
