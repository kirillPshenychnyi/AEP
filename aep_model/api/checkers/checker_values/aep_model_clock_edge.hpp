#ifndef __AEP_MODEL_CLOCK_EDGE_HPP__
#define __AEP_MODEL_CLOCK_EDGE_HPP__

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct ClockEdge
{

/***************************************************************************/

	enum class Kind
	{
			OVL_POSEDGE
		,	OVL_NEGEDGE

		,	Default = OVL_POSEDGE
	};
	
/***************************************************************************/

	static const char * const toString( Kind _enum )
	{
		switch ( _enum )
		{
			case Kind::OVL_POSEDGE:
				return "`OVL_POSEDGE";
			case Kind::OVL_NEGEDGE:
				return "`OVL_NEGEDGE";
			default:
				return toString( Kind::Default );
		}
	} 

/***************************************************************************/

};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_CLOCK_EDGE_HPP__
