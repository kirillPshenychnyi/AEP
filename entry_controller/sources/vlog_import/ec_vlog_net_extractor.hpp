#ifndef __EC_VLOG_NET_EXTRACTOR_HPP__
#define __EC_VLOG_NET_EXTRACTOR_HPP__

/***************************************************************************/

#include "entry_controller\sources\vlog_import\ec_vlog_base_importer.hpp"

#include "vlog_data_model\api\vlog_dm_fwd.hpp"
#include "vlog_data_model\api\vlog_dm_net_type.hpp"
#include "vlog_data_model\api\vlog_dm_dimension.hpp"
#include "vlog_data_model\api\vlog_dm_location.hpp"

#include <boost\optional.hpp>
#include <boost\function.hpp>

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
		std::vector< VlogDM::DimensionPtr >
		Dimensions;

	typedef
		std::function< VlogDM::DimensionPtr( VlogDM::Location, VlogDM::RangePtr ) >
		RangeCreator;

/***************************************************************************/

public:

/***************************************************************************/

	NetExtractor( VlogDM::IAccessor & _accessor );

/***************************************************************************/

	void extract( antlr4::ParserRuleContext & _context );

	VlogDM::DimensionPtr getDimension();

/***************************************************************************/

private:

/***************************************************************************/

	antlrcpp::Any visitNet_type( Verilog2001Parser::Net_typeContext *ctx ) override ;

	antlrcpp::Any visitRange( Verilog2001Parser::RangeContext *ctx ) override;

	antlrcpp::Any visitDimension( Verilog2001Parser::DimensionContext *ctx ) override;

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
		,	RangeCreator _creator 
	);

/***************************************************************************/

public:

/***************************************************************************/

	Ports m_netIds;

	std::unique_ptr< VlogDM::Type > m_type;
	
	Dimensions m_dimensions;

	VlogDM::NetKind::Kind m_netType;

	bool m_isReg;

/***************************************************************************/

};

/***************************************************************************/

}
}

/***************************************************************************/

#endif // !__EC_VLOG_NET_EXTRACTOR_HPP__
