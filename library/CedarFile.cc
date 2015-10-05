/*******************************************************************
 * CLASS CedarFile - Definition
 *
 ******************************************************************/

// This file is part of the Cedar++ library, A C++ library used to read the
// Cedar data format

// Copyright (c) 2004,2005 University Corporation for Atmospheric Research
// Author: Jose Garcia <jgarcia@ucar.edu> and Patrick West <pwest@ucar.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You can contact University Corporation for Atmospheric Research at
// 3080 Center Green Drive, Boulder, CO 80301
 
// (c) COPYRIGHT University Corporation for Atmospheric Research 2004-2005
// Please read the full copyright statement in the file COPYRIGHT_UCAR.
//
// Authors:
//      jgarcia     Jose Garcia <jgarcia@ucar.edu>
//      pwest       Patrick West <pwest@ucar.edu>

#include "CedarConfig.h"
#include "CedarErrorHandler.h"
#include "CedarFile.h"
#include "CedarCrayBlockingFormat.h"
#include "CedarMadrigalFormat.h"
#include "CedarException.h"

using std::cout ;
using std::endl ;

CedarFile::CedarFile(int check_blocks, int format)
{
    f = 0 ;
    switch( format )
    {
	case CEDARFILE_ABSTRACT_FACTORY:
	    with_check_sum = check_blocks ;
	    f = 0 ;
	    break ;
	case CRAY_BLOCKING_FORMAT:
	    with_check_sum = check_blocks ;
	    f = new CedarCrayBlockingFormat( check_blocks ) ;
	    break ;
	case MADRIGAL_FORMAT:
	    with_check_sum = check_blocks ;
	    f = new CedarMadrigalFormat( check_blocks ) ;
	    break ;
	default:
	    CedarErrorHandler::errorT( CEDARFILE__EXIT__UNKNOWN_FORMAT,
	                               "s", CEDARFILE__FATAL__UNKNOWN_FORMAT ) ;
	    break ;
    }
}
  
CedarFile::~CedarFile()
{
    if( f )
    {
	delete f ; f = 0 ;
    }
}

inline void
CedarFile::determine_file( const char *file_name )
{
    bool determined = false ;
    try
    {
	f = new CedarCrayBlockingFormat( with_check_sum ) ;
	f->open_file( file_name ) ;
	if( f->get_first_logical_record() )
	{
	    if( f->get_next_logical_record() )
	    {
		determined = true ;
	    }
	}
    }
    catch( CedarException &e )
    {
	if( f )
	{
	    delete f ; f = 0 ;
	}

	COUT( cout << "Is not a cbf file: "
	      << e.get_description() << endl ; )
	try
	{
	    f = new CedarMadrigalFormat( with_check_sum ) ;
	    f->open_file( file_name ) ;
	    if( f->get_first_logical_record() )
	    {
		if( f->get_next_logical_record() )
		{
		    determined = true ;
		}
	    }
	}
	catch( CedarException &e )
	{
	    if( f )
	    {
		delete f ; f = 0 ;
	    }

	    COUT( cout << "Is not a madrigal file: "
	          << e.get_description() << endl ; )
	}
	catch(...)
	{
	    if( f )
	    {
		delete f ; f = 0 ;
	    }
	}
    }
    catch(...)
    {
	if( f )
	{
	    delete f ; f = 0 ;
	}
    }
    if( !determined )
    {
	CedarErrorHandler::errorT( CEDARFILE__EXIT__UNKNOWN_FORMAT, "s",
				   CEDARFILE__FATAL__UNKNOWN_FORMAT ) ;
    }
}

void CedarFile::open_file(const char *file_name)
{
  if (file_name==NULL)
    {
      CedarErrorHandler::errorT(CEDARFILE__EXIT__FILENAME_NULL,"s",CEDARFILE__FATAL__FILENAME_NULL);
    }
  if (!f)
    {
      determine_file(file_name);
      f->rewind();
    }
  else
    f->open_file(file_name);

}
