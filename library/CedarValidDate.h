/*******************************************************************
* CLASS CedarValidDate - Declaration
*
*******************************************************************/

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

#ifndef CedarValidDate_h_
#define CedarValidDate_h_ 1

#include "CedarDataTypes.h"

/**
 * Validates values used for date_field variables in the CEDAR API.
 * All the member functions are declared static so you do not need
 * to instantiate an object to call these functions. Use a syntax like:
 * "CedarValidDate::validate_year(1998);" to access the routines.
 * Documentation not ready.
 */
class CedarValidDate
{
public:
  /// Returns 1 if the number given as the parameter is in the range [1900,2100], else returns 0.
  static int validate_year(date_field);
  /// Returns 1 if the number given as the parameter is a leap year, else returns 0.
  static int is_leap_year(date_field);
  /// Returns 1 if the number given as the parameter is a valid month-day numeric combination, else returns 0.
  static int validate_date(date_field);
  /// Returns 1 if the number given as the parameter is a valid month-day numeric combination in leap year , else returns 0.
  static int validate_date_in_leap_year(date_field);
  /// Returns 1 if the number given as the parameter is a valid hour-minute numeric combination, else returns 0.
  static int validate_hour_minute(date_field);
  /// Returns 1 if the number given as the parameter is in the range [0,5999], else returns 0.
  static int validate_second_centisecond(date_field);
  /**
   * Returns the Julian date value for a month-day numeric combination defined in the first parameter given the year
   * defined by the second parameter. If the first parameter is not a valid  month-day numeric combination or the
   * second parameter is not a valid year as defined by validate_year returns 0.
   */
  static date_field change_cedar_to_julian_format(date_field, date_field);
  /**
   * Returns the cedar date value as a month-day numeric combination for the Julian date defined in the first parameter
   * given the year defined by the second parameter. If the first parameter is not a valid  Julian date or the second 
   * parameter is not a valid year as defined by validate_year returns 0.
   */
  static date_field change_julian_to_cedar_format(date_field, date_field);
};

#endif	// CedarValidDate_h_
