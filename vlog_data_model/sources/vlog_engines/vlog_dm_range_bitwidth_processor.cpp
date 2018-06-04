#include "stdafx.h"

#include "vlog_data_model\sources\vlog_engines\vlog_dm_range_bitwidth_processor.hpp"
#include "vlog_data_model\sources\vlog_engines\vlog_dm_bitwidth_calculator.hpp"

#include "vlog_data_model\sources\model\vlog_dm_primary_literal_impl.hpp"

#include "vlog_data_model\api\vlog_dm_expression_cast.hpp"
#include "vlog_data_model\api\vlog_dm_part_select_range.hpp"
#include "vlog_data_model\api\vlog_dm_expression_range.hpp"
#include "vlog_data_model\api\vlog_dm_multidimensional_range.hpp"

#include <boost\lexical_cast.hpp>

/***************************************************************************/

namespace VlogDM {
namespace VlogEngines {

/***************************************************************************/

RangeBitwidthProcessor::RangeBitwidthProcessor()
	:	m_result( 1 )
{
}

/***************************************************************************/

int 
RangeBitwidthProcessor::calculate( Range const & _range )
{
	_range.accept( *this );

	return m_result;
}

/***************************************************************************/

void
RangeBitwidthProcessor::visit( ExpressionRange const & _range )
{
	BitwidthCalculator expressionBitwidth;

	m_result = expressionBitwidth.calculate( _range.getExpression() );
}

/***************************************************************************/

void 
RangeBitwidthProcessor::visit( PartSelectRange const & _range )
{
	ExpressionCast< PrimaryLiteral > literalCaster;

	auto lhsRange = literalCaster.cast( _range.getLeftBound() );

	if( !lhsRange )
		return;

	auto rhsRange = literalCaster.cast( _range.getRightBound() );

	if( !rhsRange )
		return;
	try
	{
		int rhs = std::stoi( lhsRange->getValue() );
		int lhs = std::stoi( rhsRange->getValue() );

		int lowBound = std::min( rhs, lhs );
		int highBound = std::max( rhs, lhs );

		m_result = highBound - lowBound + 1;
	}
	catch( std::exception const & _ex )
	{

	}
}

/***************************************************************************/

void 
RangeBitwidthProcessor::visit( MultidimensionalRange const & _range )
{
	const int nRanges = _range.getRangesCount();

	for( int i = 0; i < nRanges; ++i )
		_range.getRange( i ).accept( *this );
}

/***************************************************************************/

}
}