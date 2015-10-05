/*******************************************************************
 * CLASS CedarDate - Declaration
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

#ifndef CedarDate_h_
#define CedarDate_h_ 1

#include <fstream>

using std::ofstream ;

#include "CedarDataTypes.h"
#include "CedarStringConversions.h"
#include "CedarValidDate.h" 

/**
 * Encapsulates data and behavior for dates in the CEDAR database.
 * Documentation not ready.
 */

class CedarDate
{
  /// Year data
  date_field year;              
  /// Month Day data
  date_field date; 
  /// Hour Minute Data
  date_field hour_min;
  /// Millisecond Data
  date_field second_centisecond;
public:
/** 
 * The class CedarDate contains the overloaded operators
 * <,   <=,   >,   >=   and ==
 * so this enumeration represents the relational operator as values
 * than can be passed as arguments  to the function validate_dates_relationship.
 * You may wish to do this for consistency and clarity:
 * validate_dates_relationship (my_date, your_date, CedarDate::minor);
 * This code is easier to read and understand than just passing an
 * integer as the last parameter. 
 */
  enum date_operator {minor, minor_equal, major, major_equal, equal};
  /// Default constructor.
  CedarDate();
  /// Set the date for this object.
  int set_date(date_field ,date_field ,date_field ,date_field);

  /**
   *@name functions to get independent year, date, hour_min and millisecond.
   * Return copys of the private member values.
   */
  //@{
  /// Returns the year value for this object.
  date_field get_year() {return year;}
  /// Returns the date value for this object.
  date_field get_month_day() {return date;}
  /// Returns the hour_min value for this object.
  date_field get_hour_min() {return hour_min;}
  /// Returns the millisecond value for this object.
  date_field get_second_centisecond() {return second_centisecond;}
  /// Returns the month corresponding to the value of the date private member for this object.
  date_field get_month()
  {
    int month=date/100;
    return month;
  };
  /// Returns the day corresponding to the value of the date private member for this object.
  date_field get_day()
  {
    int month=date/100;
    int day=date-month*100;
    return day;
  }
  ///
  date_field get_hour()
  {
    return (hour_min/100);
  }
  ///
  date_field get_minute()
  {
    return (hour_min-((hour_min/100)*100));
  }
  //@}
  
/**
   *@name Overloaded operators for comparison 
   * Relational operators to facilitate the logical operations.
   */
  //@{
    /// minor relational operator.
         int operator<(CedarDate &);
    /// major relational operator.
         int operator>(CedarDate &);
    /// minor equal relational operator.
	 int operator<=(CedarDate &);
    /// major equal relational operator.
	 int operator>=(CedarDate &);
    /// equal relational operator.
	 int operator==(CedarDate &);
  //@}
  /// Validates that the date_field values passed as arguments to the object are valid numbers.
  int validate_fields(date_field ,date_field ,date_field ,date_field);
  /// Function to validate a given relationship for two dates.
  int validate_dates_relationship(CedarDate &, CedarDate &, int);
  /// Function to save the date as text via a ofstream object. 
  void save_date_us_format(ofstream &);
  /// Function to save the time as text via a ofstream object. 
  void save_time_us_format(ofstream &);
  ///Functions to get a pre formatted date as a text string.
  char* get_date_us_format(char *);
};

#endif // CedarDate_h_


