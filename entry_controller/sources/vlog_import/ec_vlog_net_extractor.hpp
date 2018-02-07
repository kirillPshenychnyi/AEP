#ifndef __EC_VLOG_NET_EXTRACTOR_HPP__
#define __EC_VLOG_NET_EXTRACTOR_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include <vector>

/***************************************************************************/

namespace EntryController {
namespace VlogImport {

/***************************************************************************/

struct NetExtractor
	:	public BaseImporter
{

/***************************************************************************/

	typedef
		std::pair< std::string, VlogDM::Location >
		NetItem;

	typedef
		std::vector< NetItem >
		Ports;

	typedef
		std::pair< NetItem, NetItem >
		Range;

	typedef
		std::vector< Range >
		Ranges;

	typedef
		std::vector< VlogDM::DimensionPtr >
		Dimensions;

/***************************************************************************/

public:

/***************************************************************************/

	NetExtractor( VlogDM::IAccessor & _accessor );

/***************************************************************************/

	void extract( antlr4::ParserRuleContext & _context );

	VlogDM::RangePtr createRange( Range const & _dimension );

	VlogDM::DimensionPtr getDimension( int _idx );

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitNet_type( 
		Verilog2001Parser::Net_typeContext *ctx 
	) override;

	antlrcpp::Any visitRange( 
		Verilog2001Parser::RangeContext *ctx 
	) override;

	antlrcpp::Any visitDimension( 
		Verilog2001Parser::DimensionContext *ctx 
	) override;

	antlrcpp::Any visitList_of_port_identifiers(
			Verilog2001Parser::List_of_port_identifiersContext *ctx 
	) override;

	antlrcpp::Any visitList_of_net_identifiers(
			Verilog2001Parser::List_of_net_identifiersContext *ctx 
	) override;

	antlrcpp::Any visitPort_identifier( 
			Verilog2001Parser::Port_identifierContext *ctx 
	) override ;

	antlrcpp::Any visitNet_identifier( 
			Verilog2001Parser::Net_identifierContext *ctx 
	) override ;

	antlrcpp::Any visitVariable_identifier(
		Verilog2001Parser::Variable_identifierContext *ctx
	) override;

/***************************************************************************/

	antlrcpp::Any visitListOfIds( antlr4::ParserRuleContext & _context );

	antlrcpp::Any extractId( antlr4::ParserRuleContext & _context );

/***************************************************************************/

	void initType();

	void initDimension(
			NetExtractor::NetItem const& _leftBound
		,	NetExtractor::NetItem const& _rightBound
	);

	void pushDimension();

/***************************************************************************/

public:

/***************************************************************************/

	Ports m_netIds;

	Dimensions m_dimensions;

	Ranges m_ranges;

	VlogDM::TypePtr m_type;
	
	VlogDM::DimensionPtr m_typeDimension;

	VlogDM::NetKind::Kind m_netType;

	bool m_isReg;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_NET_EXTRACTOR_HPP__
