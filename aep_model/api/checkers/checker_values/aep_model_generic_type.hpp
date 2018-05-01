#ifndef __AEP_MODEL_GENERIC_TYPE_HPP__
#define __AEP_MODEL_GENERIC_TYPE_HPP__

/***************************************************************************/

namespace AepModel {

/***************************************************************************/

struct GenericType
{

/***************************************************************************/

	enum class Kind
	{
			SeverityLevel
		,	PropertyType
		,	ClockEdge
		,	CoverageLevel
		,	ResetPolarity
		,	GatingType
		,	Msg

		,	ValueType
		,	MinCycles
		,	MaxCycles
		,	MinAcknowledgeCycles
		,	MaxAcknowledgeCycles
		,	MaxAcknowledgeLength
		,	RequestDrop
		,	DeassertionCount
		,	Width
		,	Value
	};

/***************************************************************************/

	static const char * const toString( Kind _enum )
	{
		switch( _enum )
		{
			case Kind::SeverityLevel:
				return "severity_level";
			case Kind::PropertyType:
				return "property_type";
			case Kind::ClockEdge:
				return "clock_edge";
			case Kind::ResetPolarity:
				return "reset_polarity";
			case Kind::GatingType:
				return "gating_type";
			case Kind::CoverageLevel:
				return "coverage_level";
			case Kind::Msg:
				return "msg";

			case Kind::ValueType:
				return "value_type";
			case Kind::MinCycles:
			return "min_cks";
			case Kind::MaxCycles:
				return "max_cks";
			case Kind::MinAcknowledgeCycles:
				return "min_ack_cycle";
			case Kind::MaxAcknowledgeCycles:
				return "max_ack_cycle";
			case Kind::MaxAcknowledgeLength:
				return "max_ack_length";
			case Kind::RequestDrop:
				return "req_drop";
			case Kind::DeassertionCount:
				return "deassert_count";
			case Kind::Width:
				return "width";
			case Kind::Value:
				return "value";

			default:
				return "";
		}
	}
};

/***************************************************************************/

}

/***************************************************************************/

#endif // !__AEP_MODEL_GENERIC_TYPE_HPP__
