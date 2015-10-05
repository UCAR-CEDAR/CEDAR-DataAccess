/*******************************************************************
 * CLASS CedarErrorHandler - Declaration
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

#ifndef CedarErrorHandler_h_
#define CedarErrorHandler_h_ 1

#include <cstddef>
#include <string>

using std::string ;

#include "CedarMessages.h"
#include "CedarErrors.h"

/// Manages all errors for the CEDAR API.
class CedarErrorHandler
{
public:
  /**
   * Error handler for the CEDAR API with undefined number of arguments.
   *
   * When an error in the CEDAR API is detected this function is call and
   * the caller does not expect errorT to return control back, that is
   * because errorT either terminates the program by calling exit with the
   * argument error_number or throws an integer exception error_number when
   * CEDAR_USE_EXCEPTIONS is defined. If you wish to send information to
   * cerr, you may pass a format string like "sisd" which means that next 4
   * arguments are pointer to char (s), integer(i), pointer to char (s),
   * double(d). Any letter different than s,i,d terminates the loop of
   * message output. If the responsibility of the caller of this function to
   * pass exactly as many letters as arguments are pass in place of (...)
   * and to get sure that the actual arguments correspond with the letter
   * indicator. For example you may pass (32,"sisds","Error: Undefined
   * control: ",27,". Status of cpd variable ",23.456,"\n") which will cause
   * this function to either exit or throw with integer value 32 and the
   * string "Error: Undefined control: 27. Status of cpd variable 23.456"
   * with a carriage return will be send to cerr. Please notice that in this
   * example you passed "sisds" as a format argument which indicated that
   * ... is equivalent to 5 more arguments in this order:
   * char*,int,char*,double,char*. If by any chance you pass '\n' (that is
   * char) as "\n" that is char* a SEGV will occur.
   */
  static void errorT( int error_number, string format, ... ) ;
} ;

#endif // CedarErrorHandler_h_

