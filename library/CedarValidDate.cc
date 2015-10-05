/*******************************************************************
 * CLASS CedarValidDate - Definition
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
#include "CedarMessages.h"
#include "CedarValidDate.h"

/* A year can be between [1900,2100] */

int CedarValidDate::validate_year(date_field year)
{
  register date_field yr=year;
  for (register date_field i = 1900; i <= 2100; i++)
    if (yr == i)
      return 1;
  return 0;
}

int CedarValidDate::is_leap_year(date_field year)
{
  int leap = year%4 == 0 && year%100 != 0 || year%400 == 0 ;
  return leap;
}


/* A second_centisecond can be between [0,5999] */

int CedarValidDate::validate_second_centisecond(date_field cs)
{
  // cs is always > 0 since it is unsigned. 
  if (cs<=5999)
    return 1;
  if (cs==6000)
    {
#ifdef CEDAR_VERBOSE
      cerr<<CEDARVALIDDATE__MSG__WARNING_INCORRECT_SECOND;
#endif
      return 1;
    }
  return 0;
}

date_field CedarValidDate::change_julian_to_cedar_format(date_field doy, date_field year)
{
  int day_tab[2][13] = { { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } ,
		         { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }};
  if (!(validate_year(year)))
      return 0;
  int leap = year%4 == 0 && year%100 != 0 || year%400 == 0 ;
  if ((leap)&&(doy>366))
    return 0;
  else if (doy>365)
    return 0;
  int i;
  for ( i=1 ; doy > day_tab[leap][i]  ; i++ ) 
    doy -= day_tab[leap][i] ;
  return i*100+doy;
}

date_field CedarValidDate::change_cedar_to_julian_format(date_field month_day, date_field year)
{
  int day_tab[2][13] = { { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
			 { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }};
  if (!(validate_year(year)))
      return 0;
  int leap = year%4 == 0 && year%100 != 0 || year%400 == 0 ;
  if (leap)
    {
      if (!(validate_date_in_leap_year(month_day)))
	return 0;
    }
  else
    {
      if (!(validate_date(month_day)))
	return 0;
    }
  int mon=month_day/100;
  int day=month_day-mon*100;
  int i;
  for ( i=1 ; i<mon ; i++ ) 
    day += day_tab[leap][i] ;
  return(day) ;
}

int CedarValidDate::validate_date(date_field month_day)
{
  int is_valid_month=0;
  int is_valid_day=0;
  int mon=month_day/100;
  int day=month_day-mon*100;
  if ((1<=mon)&&(mon<=12))
    is_valid_month=1;
  if (((mon==1)||(mon==3)||(mon==5)||(mon==7)||(mon==8)||(mon==10)||(mon==12))&&((1<=day)&&(day<=31)))
    is_valid_day=1; 
  if (((mon==4)||(mon==6)||(mon==9)||(mon==11))&&((1<=day)&&(day<=30)))
    is_valid_day=1;
  if ((mon==2)&&((1<=day)&&(day<=28)))
    is_valid_day=1;
  return (is_valid_month&&is_valid_day);
}

int CedarValidDate::validate_date_in_leap_year(date_field month_day)
{
  int is_valid_month=0;
  int is_valid_day=0;
  int mon=month_day/100;
  int day=month_day-mon*100;
  if ((1<=mon)&&(mon<=12))
    is_valid_month=1;
  if (((mon==1)||(mon==3)||(mon==5)||(mon==7)||(mon==8)||(mon==10)||(mon==12))&&((1<=day)&&(day<=31)))
    is_valid_day=1; 
  if (((mon==4)||(mon==6)||(mon==9)||(mon==11))&&((1<=day)&&(day<=30)))
    is_valid_day=1;
  if ((mon==2)&&((1<=day)&&(day<=29)))
    is_valid_day=1;
  return (is_valid_month&&is_valid_day);
}

int CedarValidDate::validate_hour_minute(date_field hour_min)
{
  int is_valid_hour=0;
  int is_valid_min=0;
  int hour=hour_min/100;
  int min=hour_min-hour*100;
  if ((0<=hour)&&(hour<=23))
    is_valid_hour=1;
  else if (hour==24)
    {
#ifdef CEDAR_VERBOSE 
      cerr<<CEDARVALIDDATE__MSG__WARNING_INCORRECT_HOUR;
#endif
      is_valid_hour=1;
    }
  if ((0<=min)&&(min<=59))
    is_valid_min=1;
  else if (min==60)
    {
#ifdef CEDAR_VERBOSE
      cerr<<CEDARVALIDDATE__MSG__WARNING_INCORRECT_MINUTE;
#endif
      is_valid_min=1;
    }  
  return (is_valid_hour&&is_valid_min);
}
