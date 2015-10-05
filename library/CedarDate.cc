/*******************************************************************
 * CLASS CedarDate - Definition
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

#include <cstring>

#include "CedarMessages.h"
#include "CedarErrors.h"
#include "CedarDate.h"

using std::endl ;

/*
 * The constructor initializes the object to the date time 1/1/1900 at 0:0 0,0
 */

CedarDate::CedarDate()
{
  year=1900;
  date=101;
  hour_min=0;
  second_centisecond=0;
};

void CedarDate::save_date_us_format(ofstream &fl)
{
  /*
   * Integer division will take only the integer part and will ignore the fractional part.
   * Not rounding is performed.
   * For example 1267/100 in an integer division will yield 12 and not 13 as you may think 
   * as the result of rounding 12.67
   */
  int month=date/100;
  int day=date-month*100;
  fl<<month<<'/'<<day<<'/'<<year<<endl;
}

void CedarDate::save_time_us_format(ofstream &fl)
{
  /* Performing integer divisions to split hour_min and second_centisecond variables */
  int hr=hour_min/100;
  int mn=hour_min-hr*100;
  int sc= second_centisecond/100;
  int ct=second_centisecond-sc*100;
  fl<<hr<<':'<<mn<<' '<<sc<<','<<ct<<endl;
}

char* CedarDate::get_date_us_format(char *pstr)
{
  strcpy (pstr,"");
  /* Performing integer divisions to split hour_min and second_centisecond variables */
  int month=date/100;
  int day=date-month*100;
  int hr=hour_min/100;
  int mn=hour_min-hr*100;
  int sc= second_centisecond/100;
  int ct=second_centisecond-sc*100;
  char buff [50];  
  /* 
   * This buffer buff  holds the conversions of the date_field values to string of char perform by ltoa.
   * strcat concatenates the pieces to the buffer received (pstr) in order to build the string.
   * The resulting string will look like "month/day/year hour:minute second,second_centisecond"
   */
  CedarStringConversions::ltoa(month,buff,10);
  strcat(pstr, buff);
  strcat(pstr, "/");
  CedarStringConversions::ltoa(day,buff,10);
  strcat(pstr, buff);
  strcat(pstr, "/");
  CedarStringConversions::ltoa(year,buff,10);
  strcat(pstr, buff);
  strcat(pstr, " ");
  CedarStringConversions::ltoa(hr,buff,10);
  strcat(pstr, buff);
  strcat(pstr, ":");
  CedarStringConversions::ltoa(mn,buff,10);
  strcat(pstr, buff);
  strcat(pstr, " ");
  CedarStringConversions::ltoa(sc,buff,10);
  strcat(pstr, buff);
  strcat(pstr, ",");
  CedarStringConversions::ltoa(ct,buff,10);
  strcat(pstr, buff);
  return pstr;
}


/*
 * set_date will set this object to a specific date if and only if the values to be used
 * (date_field f1,date_field f2,date_field f3,date_field f4) are valid.
 * when you try to set a date if you get TRUE=1 then the process went OK, otherwise you will get
 * FALSE=0 because the member validate_fields did not like the (f1, f2, f3, f4) values
 */

int CedarDate::set_date(date_field f1,date_field f2,date_field f3,date_field f4)
{
  if (validate_fields(f1, f2, f3, f4))
    { 
      year=f1; date=f2; hour_min=f3; second_centisecond=f4;
      return 1;
    }
  else
    return 0;
}

int CedarDate::operator<(CedarDate &dt)
{
  if(year<dt.year) return 1;
  else
    {
      if (year>dt.year) return 0;
      else //same year
	{
	  if (date<dt.date) return 1;
	  else
	    {
	      if (date>dt.date) return 0;
	      else //same date
		{
		  if(hour_min<dt.hour_min) return 1;
		  else
		    {
		      if (hour_min>dt.hour_min) return 0;
		      else //same hour_min
			{
			  if (second_centisecond<dt.second_centisecond) return 1;
			  else 
			    {
			      if (second_centisecond>dt.second_centisecond) return 0;
			      else //same second_centisecond
				{
				  return 0;
				}
			    }
			}
		    }
		}
	    }
	}
    }
}

int CedarDate::operator<=(CedarDate &dt)
{
  if(year<dt.year) return 1;
  else
    {
      if (year>dt.year) return 0;
      else //same year
	{
	  if (date<dt.date) return 1;
	  else
	    {
	      if (date>dt.date) return 0;
	      else //same date
		{
		  if(hour_min<dt.hour_min) return 1;
		  else
		    {
		      if (hour_min>dt.hour_min) return 0;
		      else //same hour_min
			{
			  if (second_centisecond<dt.second_centisecond) return 1;
			  else 
			    {
			      if (second_centisecond>dt.second_centisecond) return 0;
			      else //same second_centisecond
				{
				  return 1;
				}
			    }
			}
		    }
		}
	    }
	}
    }
}

int CedarDate::operator>(CedarDate &dt)
{
  if(year<dt.year) return 0;
  else
    {
      if (year>dt.year) return 1;
      else //same year
	{
	  if (date<dt.date) return 0;
	  else
	    {
	      if (date>dt.date) return 1;
	      else //same date
		{
		  if(hour_min<dt.hour_min) return 0;
		  else
		    {
		      if (hour_min>dt.hour_min) return 1;
		      else //same hour_min
			{
			  if (second_centisecond<dt.second_centisecond) return 0;
			  else 
			    {
			      if (second_centisecond>dt.second_centisecond) return 1;
			      else //same second_centisecond
				{
				  return 0;
				}
			    }
			}
		    }
		}
	    }
	}
    }
}

int CedarDate::operator>=(CedarDate &dt)
{
  if(year<dt.year) return 0;
  else
    {
      if (year>dt.year) return 1;
      else //same year
	{
	  if (date<dt.date) return 0;
	  else
	    {
	      if (date>dt.date) return 1;
	      else //same date
		{
		  if(hour_min<dt.hour_min) return 0;
		  else
		    {
		      if (hour_min>dt.hour_min) return 1;
		      else //same hour_min
			{
			  if (second_centisecond<dt.second_centisecond) return 0;
			  else 
			    {
			      if (second_centisecond>dt.second_centisecond) return 1;
			      else //same second_centisecond
				{
				  return 1;
				}
			    }
			}
		    }
		}
	    }
	}
    }
}

int CedarDate::operator==(CedarDate &dt)
{
  if(year!=dt.year) return 0;
  if(date!=dt.date) return 0;
  if(hour_min!=dt.hour_min) return 0;
  if(second_centisecond!=dt.second_centisecond) return 0;
  return 1;
}

int CedarDate::validate_fields(date_field yr, date_field dt, date_field hm, date_field cs)
{
  /*
   * We depend on the static member functions of CedarValidDate class to perform validation routines.
   * These flags  mantain the information returned by the static member functions for CedarValidDate.
   */
  int year_ok=0;
  int date_ok=0;
  int hour_min_ok=0;
  int second_centisecond_ok=0;
  // Starting validation...
  year_ok=CedarValidDate::validate_year(yr);
  if (CedarValidDate::is_leap_year(yr))
    date_ok=CedarValidDate::validate_date_in_leap_year(dt);
  else
    date_ok=CedarValidDate::validate_date(dt);
   hour_min_ok=CedarValidDate::validate_hour_minute(hm);
   second_centisecond_ok=CedarValidDate::validate_second_centisecond(cs);
  // Finally we calculate the return value of this function by 'AND' all the flags 
   if (year_ok && date_ok && hour_min_ok && second_centisecond_ok)
     return 1;
   else 
     return 0;
}

/*
 * validate_dates_relationship uses two CedarDate objects (d1, d2) and the integere 
 * op to validate the "op" relationship between the objects. 
 * op should only take the values specify in the enum date_operator of CedarDate that is:
 * minor, minor_equal, major, major_equal, equal
 * If op is a valid relationship type and the relationship is valid 1 is returned, else 0 is returned
 * If op is not valid relationship type -1 is returned to indicated an error in the parameters
 */

int CedarDate::validate_dates_relationship(CedarDate &d1, CedarDate &d2, int op)
{
  if (op==(CedarDate::equal))
    {
      if (d1==d2) return 1;
      else return 0;
    }
  if (op==(CedarDate::minor))
    {
      if (d1<d2) return 1;
      else return 0;
    }
  if (op==(CedarDate::minor_equal))
    {
      if (d1<=d2) return 1;
      else return 0;
    }
  if (op==(CedarDate::major))
    {
      if (d1>d2) return 1;
      else return 0;
    }
  if (op==(CedarDate::major_equal))
    {
      if (d1>=d2) return 1;
      else return 0;
    }
  return -1;
}

