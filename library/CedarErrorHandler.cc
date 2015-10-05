/*******************************************************************
 * CLASS CedarErrorHandler - Definition
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

#include <cstdarg>

#include "CedarConfig.h"
#include "CedarErrorHandler.h"
#include "CedarException.h"
#include "CedarString.h"

using std::cerr ;

void CedarErrorHandler::errorT( int error_number, string format, ... )
{
    CedarString des = "" ;
    if( !format.empty() )
    {
	des =des + "Cedar++: " ;
	//const time_t sctime=time(NULL);
	//const struct tm *sttime=localtime(&sctime); 
	//des=des+"Error time; ";
	//des=des+asctime(sttime);
	int count = 0 ;
	int total_number_strings = format.length() ;
	va_list arg_ptr;
	va_start( arg_ptr, format.c_str() ) ;
	while( count < total_number_strings )
	{
	    // character and float are not supported because of data
	    // conversion before the call for arguments for which there is not
	    // parameter present in the function prototype See "The C++
	    // Programming Language" Bjarne Stroustrup Second Edition.
	    // Pag.495, section r.5.2.2
	    switch( format[count] )
	    {
		case 's':
		    des = des + va_arg( arg_ptr, char* ) ;
		    break ;
		case 'i':
		    des = des + va_arg( arg_ptr, int ) ;
		    break ;
		case 'd':
		    des = des + va_arg( arg_ptr, double ) ;
		    break ;
		default:
		    // If we get an unrecognize character we terminate the loop.
		    count = total_number_strings ;
		    break ;
	    }
	    count++ ;
	}
	va_end( arg_ptr ) ;
    }
#ifdef CEDAR_USE_EXCEPTIONS
    throw CedarException( error_number, des.c_str() ) ;
#else
    cerr << des ;
    exit( error_number ) ;
#endif // CEDAR_USE_EXCEPTIONS
}
