#ifndef __VLOG_DM_LOCATION_HPP__
#define __VLOG_DM_LOCATION_HPP__

/***************************************************************************/

namespace VlogDM
{

/***************************************************************************/
	
struct Location
{
	
/***************************************************************************/
		
	Location()
		:	m_file( "" )
		,	m_beginLine( 0 )
		,	m_beginColumn( 0 )
		,	m_endLine( 0 )
		,	m_endColumn( 0 )
	{
	}

	Location( std::string const & _file, int _beginLine, int _beginColumn )
		:	m_file( _file )
		,	m_beginLine( _beginLine )
		,	m_beginColumn( _beginColumn )
		,	m_endLine( 0 )
		,	m_endColumn( 0 )
	{
	}

	Location( Location const& _location )
		:	m_file( _location.m_file )
		,	m_beginLine( _location.m_beginLine )
		,	m_beginColumn( _location.m_beginColumn )
		,	m_endLine( 0 )
		,	m_endColumn( 0 )
	{
	}

	Location( Location && _location )
		:	m_file( _location.m_file )
		,	m_beginLine( _location.m_beginLine )
		,	m_beginColumn( _location.m_beginColumn )
		,	m_endLine( 0 )
		,	m_endColumn( 0 )
	{
	}

	Location& operator = ( const Location & _location )
	{
		m_file = _location.m_file;
		m_beginLine = _location.m_beginLine;
		m_beginColumn = _location.m_beginColumn;
		m_endLine = 0;
		m_endColumn = 0;

		return *this;
	}

/***************************************************************************/

	std::string m_file;
	int m_beginLine;
	int m_beginColumn;
	int m_endLine;
	int m_endColumn;

/***************************************************************************/

};

/***************************************************************************/

}

#endif // !__VLOG_DM_LOCATION_HPP__

