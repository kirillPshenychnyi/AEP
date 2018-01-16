#ifndef __VLOG_DM_LOCATION_HPP__
#define __VLOG_DM_LOCATION_HPP__

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/
	
struct Location
{
	
/***************************************************************************/
		
	Location( std::string const & _file, int _beginLine, int _beginColumn )
		:	m_file( _file )
		,	m_beginLine( _beginLine )
		,	m_beginColumn( _beginColumn )
		,	m_endLine( 0 )
		,	m_endColumn( 0 )
	{

	}

/***************************************************************************/

	const std::string m_file;
	const int m_beginLine;
	const int m_beginColumn;
	const int m_endLine;
	const int m_endColumn;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_LOCATION_HPP__

