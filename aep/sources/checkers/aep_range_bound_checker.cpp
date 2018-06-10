#include "stdafx.h"

#include "aep\sources\checkers\aep_range_bound_checker.hpp"
#include "aep\sources\checkers\resources\aep_checker_resources.hpp"

#include "aep\api\aep_iaccessor.hpp"

#include "vlog_data_model\api\vlog_dm_continuous_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_blocking_assignment.hpp"
#include "vlog_data_model\api\vlog_dm_binary_operator.hpp"
#include "vlog_data_model\api\vlog_dm_expression.hpp"
#include "vlog_data_model\api\vlog_dm_primary_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_base_identifier.hpp"
#include "vlog_data_model\api\vlog_dm_declared.hpp"
#include "vlog_data_model\api\vlog_dm_declaration.hpp"
#include "vlog_data_model\api\vlog_dm_type.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_variable.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_expression_range.hpp"
#include "vlog_data_model\api\vlog_dm_multidimensional_range.hpp"
#include "vlog_data_model\api\vlog_dm_part_select_range.hpp"
#include "vlog_data_model\api\vlog_dm_range_cast.hpp"
#include "vlog_data_model\api\vlog_dm_expression_cast.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"
#include "vlog_data_model\api\vlog_dm_type.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_range_visitor.hpp"
#include "vlog_data_model\ih\visitors\vlog_dm_declared_visitor.hpp"

#include "aep_model\api\aep_model_iaccessor.hpp"
#include "aep_model\api\contexsts\aep_model_assertion_context.hpp"
#include "aep_model\api\checkers\aep_model_ovl_checkers_factory.hpp"
#include "aep_model\api\checkers\ovl\checker_builders\aep_model_always_checker_builder.hpp"
#include "aep_model\api\checkers\ovl\aep_model_ovl_checker.hpp"

#include "common_tools\utils\string_utils.hpp"

#include <boost\lexical_cast.hpp>

/***************************************************************************/

namespace Aep {

/***************************************************************************/

RangeBoundChecker::RangeBoundChecker( IAccessor & _aep )
	:	BaseAepChecker( _aep )
	,	m_idsQuery(
			std::bind( 
					&RangeBoundChecker::checkId
				,	this
				,	std::placeholders::_1 
			)
		)
{
}

/***************************************************************************/

void 
RangeBoundChecker::analyze()
{
	auto processCallback 
		= [ & ]( auto const & _process ) { onProcess( _process ); };

	browseProcesses< VlogDM::ContinuousAssignment >( processCallback );
	browseProcesses< VlogDM::BehavioralProcess >( processCallback );
}

/***************************************************************************/

template< typename _TProcess >
void 
RangeBoundChecker::onProcess( _TProcess const & _process )
{
	m_idsQuery.query( _process );
}

/***************************************************************************/

void 
RangeBoundChecker::checkId( VlogDM::PrimaryIdentifier const & _id )
{
	using namespace VlogDM;

	struct ExpressionRangeExtractor
		:	public RangeVisitor
	{
		using Range2Dimension = std::pair< const Expression *, int >;

		void visit( ExpressionRange const & _expressionRange ) final
		{
			ExpressionCast< PrimaryLiteral > literalCaster;

			Expression const & rangeExpression = _expressionRange.getExpression();

			if( !literalCaster.cast( rangeExpression ) )
				m_extracted.emplace_back( &rangeExpression, m_currentDimension );

			++m_currentDimension;
		}

		void visit( PartSelectRange const & _partSelect ) final
		{
			++m_currentDimension;
		}

		void visit( MultidimensionalRange const & _multi ) final
		{
			const int rangesCount = _multi.getRangesCount();

			for( int i = 0; i < rangesCount; ++i )
				_multi.getRange( i ).accept( *this );
		}

		std::vector< Range2Dimension > m_extracted;

		int m_currentDimension = 0;
	};

	static const unsigned int s_base = 2;

	auto range = _id.getIdentifier().getRange();

	if( !range )
		return;
	
	ExpressionRangeExtractor extractor;
	range->accept( extractor );

	for( auto const & rangeItem : extractor.m_extracted )
	{
		int maxBound = getMaxBoundOfDimension( rangeItem.second, _id );
		int rangeExpressionWidth = calculateBitwidth( *rangeItem.first );
		if( s_base << ( rangeExpressionWidth - 1 ) > maxBound )
			registerAssertion( *rangeItem.first, _id, maxBound );
	}
}

/***************************************************************************/

int 
RangeBoundChecker::getMaxBoundOfDimension( 
		int _dimension
	,	VlogDM::PrimaryIdentifier const & _id 
)
{
	using namespace VlogDM;

	struct MaxBoundExtractor
		:	public DeclaredVisitor
	{
		MaxBoundExtractor( int _dimension )
			:	m_dimension( _dimension )
			,	m_maxBound( 0 )
		{
		}

		void visit( Port const & _port ) final
		{
			// port may have only one packed range
			auto dimension = _port.getDeclaration().getType().getDimension();
			assert( dimension );
			processRange( dimension->getRange() );
		}

		void visit( Variable const & _var ) final
		{
			int nArrayDimensions{ 0 };

			RangeCast< MultidimensionalRange > rangeCaster;

			// array dimension
			if( auto dimension = _var.getDimension() )
			{
				Range const & range = dimension->getRange();

				nArrayDimensions = 1;

				if( auto castRes = rangeCaster.cast( range ) )
				{
					nArrayDimensions = castRes->getRangesCount();
					if( m_dimension < nArrayDimensions )
					{
						processRange( castRes->getRange( m_dimension ) );
						return;
					}
				}
				else if( m_dimension == 0 )
				{
					processRange( static_cast< PartSelectRange const& >( range ) );
					return;
				}
			}

			Type const & varType = _var.getDeclaration().getType();

			auto declDimension = varType.getDimension();
			assert( declDimension );

			Range const & typeRange = declDimension->getRange();

			if( auto castRes = rangeCaster.cast( typeRange ) )
			{
				processRange( castRes->getRange( m_dimension - nArrayDimensions ) );
			}
			else
			{
				processRange( static_cast< PartSelectRange const& >( typeRange ) );
			}
		}

		void processRange( Range const & _range )
		{
			RangeCast< PartSelectRange > rangeCaster;
			ExpressionCast< PrimaryLiteral > literalCaster;

			auto partSelRange = rangeCaster.cast( _range );
			assert( partSelRange );

			auto lhsLiteral = literalCaster.cast( partSelRange->getLeftBound() );
			auto rhsLiteral = literalCaster.cast( partSelRange->getRightBound() );

			assert( lhsLiteral && rhsLiteral );

			m_maxBound 
				=	std::max(
							boost::lexical_cast< int >( lhsLiteral->getValue() )
						,	boost::lexical_cast< int >( rhsLiteral->getValue() )
					);
		}

		const int m_dimension;
		int m_maxBound;
	};

	Declared const & declared = _id.getIdentifier().getDeclared();
	MaxBoundExtractor extractor( _dimension );

	declared.accept( extractor );

	return extractor.m_maxBound;
}

/***************************************************************************/

void 
RangeBoundChecker::registerAssertion( 
		VlogDM::Expression const & _selExpression
	,	VlogDM::PrimaryIdentifier const & _id 
	,	int _maxBound 
)
{
	using namespace AepModel;

	AssertionContext & context = retrieveAssertionContext();

	context.addChecker( createChecker( context, _selExpression, _id, _maxBound ) );

	addInputPorts( _selExpression, context );

	m_currentSuspectNumber++;
}

/***************************************************************************/

std::unique_ptr< AepModel::OvlChecker >
RangeBoundChecker::createChecker(
		AepModel::AssertionContext & _context
	,	VlogDM::Expression const & _selExpression
	,	VlogDM::PrimaryIdentifier const & _id 
	,	int _maxBound
)
{
	using namespace AepModel;
	using namespace Resources::RangeBoundChecker;

	AepModel::IAccessor const & aepAccessor = m_accessor.getAepModel();

	auto checker 
		=	aepAccessor.getCheckersFactory().newOvlAlwaysChecker(
				Tools::fillTemplate( CheckerInstanceName, m_currentSuspectNumber )
				,	_selExpression.getLocation().m_file
				,	_selExpression.getLocation().m_beginLine
			);
	
	checker->setTestExpression(
			Tools::fillTemplate( CheckExpressionWire, m_currentSuspectNumber )
		,	Tools::fillTemplate(
					CheckExpression
				,	regenerateExpression( _selExpression )
				,	_maxBound + 1
			)
	);
	checker->setFire( Tools::fillTemplate( FireWire, m_currentSuspectNumber ) );

	checker->setMessage( 
		Tools::fillTemplate( 
				Message
			,	_id.getIdentifier().getName()
			,	_id.getLocation().m_file
			,	_id.getLocation().m_beginLine
		) 
	);

	setControls( *checker );
	setEnable( _context, m_idsQuery, *checker );

	return checker->releaseChecker();
}

/***************************************************************************/

}