#ifndef __VLOG_IMPORT_TEST_BASE_NET_FIXTURE_HPP__
#define __VLOG_IMPORT_TEST_BASE_NET_FIXTURE_HPP__

/***************************************************************************/

#include "vlog_import_tests\sources\fixtures\vlog_import_base_fixture.hpp"

#include "vlog_data_model\api\vlog_dm_port_directrion.hpp"
#include "vlog_data_model\api\vlog_dm_net_kind.hpp"

#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_part_select_range.hpp"
#include "vlog_data_model\api\vlog_dm_primary_literal.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"
#include "vlog_data_model\api\vlog_dm_variable_type.hpp"
#include "vlog_data_model\api\vlog_dm_design_unit.hpp"
#include "vlog_data_model\api\vlog_dm_multidimensional_range.hpp"

#include "vlog_data_model\api\vlog_dm_declared_cast.hpp"
#include "vlog_data_model\api\vlog_dm_range_cast.hpp"
#include "vlog_data_model\api\vlog_dm_expression_cast.hpp"
#include "vlog_data_model\api\vlog_dm_type_cast.hpp"
#include "vlog_data_model\api\vlog_dm_variable.hpp"
#include "vlog_data_model\api\vlog_dm_port.hpp"
#include "vlog_data_model\api\vlog_dm_declaration.hpp"

#include "vlog_data_model\api\vlog_dm_iaccessor.hpp"

#include <vector>

/***************************************************************************/

namespace VlogModelImportTests {

/***************************************************************************/

#define RANGE( _left, _right ) \
	std::make_pair( #_left, #_right )

/***************************************************************************/

template< typename _Declared >
class BaseNetFixture
	:	public BaseFixture
{

/***************************************************************************/

	struct NetHelper
	{
		typedef
			std::pair< std::string, std::string >
			Range;

		typedef
			std::vector< Range >
			MultidimensionalRanges;

		NetHelper( BaseNetFixture< _Declared > & _parent, _Declared const & _declared )
			:	m_parent( _parent )
			,	m_declared( _declared )
		{}

		NetHelper & expectArrayBounds( Range const & _range )
		{
			return checkRange( m_declared, _range );
		}

		NetHelper & expectArrayBounds( MultidimensionalRanges _ranges )
		{
			using namespace VlogDM;

			auto dimension = m_declared.getDimension();
			REQUIRE( dimension.is_initialized() );

			VlogDM::Range const & simpleRange = dimension->getRange();
			
			MultidimensionalRange const & multidimRange
				=	BaseFixture::checkCast< 
							VlogDM::Range
						,	MultidimensionalRange
						,	RangeCast
					>( simpleRange );

			const int dimensionsCount = multidimRange.getRangesCount();

			REQUIRE( dimensionsCount == _ranges.size() );

			for( int i = 0; i < dimensionsCount; ++i )
				checkRange( multidimRange.getRange( i ), _ranges[ i ] );

			return *this;
		}

		NetHelper & expectBounds( Range const & _range )
		{
			return checkRange( m_declared.getDeclaration().getType(), _range );
		}

		NetHelper & expectNetType( VlogDM::NetKind::Kind _kind )
		{
			using namespace VlogDM;

			checkType< NetType, NetKind >( _kind );

			return *this;
		}

		NetHelper & expectRegType()
		{
			using namespace VlogDM;
	
			checkType< VariableType, VariableKind >( VariableKind::Kind::reg );

			return *this;
		}

		NetHelper & expectDirection( VlogDM::PortDirection::Direction _direction )
		{
			REQUIRE( _direction == m_declared.getDirection() );

			return *this;
		}

		template < typename _TargetType, class _Kind >
		void checkType( typename _Kind::Kind _kind )
		{
			using namespace VlogDM;

			_TargetType const & type
				=	BaseFixture::checkCast< Type, _TargetType, TypeCast >( 
							m_declared.getDeclaration().getType() 
					); 
			
			REQUIRE( _kind == type.getKind() );
		}
		
		template< typename _Dimensional >
		NetHelper & checkRange( 
				_Dimensional const & _dimensional
			,	Range const & _range
		)
		{
			auto dimension = _dimensional.getDimension();
			REQUIRE( dimension.is_initialized() );

			VlogDM::Range const & actualRange = dimension->getRange();
	
			return checkRange( actualRange, _range );	
		}

		NetHelper & checkRange( VlogDM::Range const & _range, Range const & _expected )
		{
			using namespace VlogDM;

			auto checkBound 
				=	[ this ] ( Expression const & _bound, std::string const & _expected )
					{
						PrimaryLiteral const & bound 
							= checkCast< Expression, PrimaryLiteral, ExpressionCast >( _bound );
				
						REQUIRE( bound.getValue() == _expected );
					};

			PartSelectRange const& boundedRange
					= checkCast< VlogDM::Range, PartSelectRange, RangeCast >( _range );

			checkBound( boundedRange.getLeftBound(), _expected.first );
			checkBound( boundedRange.getRightBound(), _expected.second );

			return *this;
		}

		BaseNetFixture< _Declared > & end()
		{
			return m_parent;
		}

		BaseNetFixture< _Declared > & m_parent;
		_Declared const & m_declared;
	};

/***************************************************************************/

public:

/***************************************************************************/
	
	typedef
		std::unique_ptr< NetHelper >
		HelperPtr;

	typedef
		std::vector< HelperPtr >
		ExpectedNets;

/***************************************************************************/

	BaseNetFixture< _Declared > & expectUnit( std::string const & _unit )
	{
		using namespace VlogDM;

		auto vlogDM = m_bootstrapper.m_container->resolve< IAccessor >();
	
		auto unit = vlogDM->findUnit( _unit );
		REQUIRE( unit.is_initialized() );

		m_currentUnit = unit.get_ptr();

		return *this;
	}

	NetHelper & expectNet( std::string const & _name )
	{
		using namespace VlogDM;

		auto declared = m_currentUnit->findDeclared( _name );
		REQUIRE( declared.is_initialized() );
		_Declared const& target
			= checkCast< Declared, _Declared, DeclaredCast >( *declared );

		m_expectedNets.emplace_back( 
			std::make_unique< NetHelper >( *this, target )
		);

		return *m_expectedNets.back();
	}

/***************************************************************************/

private:

/***************************************************************************/

	ExpectedNets m_expectedNets;

	const VlogDM::DesignUnit * m_currentUnit;

/***************************************************************************/

};

/***************************************************************************/

} 

/***************************************************************************/

#endif // !__VLOG_IMPORT_TEST_BASE_NET_FIXTURE_HPP__
