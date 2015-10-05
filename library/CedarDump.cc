/*******************************************************************
 * CLASS CedarDump - Definition
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
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <fstream>

using std::ofstream ;
using std::ios ;
using std::endl ;

#include "CedarDump.h"
#include "CedarErrorHandler.h"


CedarDump *CedarDump::_instance = 0 ;
int       CedarDump::counter;
ofstream  CedarDump::file_buffer;

/* 
   Because of the nature of CedarDump objects (To log execution messages for the Cedar API)
   the constructors and the destructor write messages to the log themselves. This is done so 
   the log display a full status of the current process 
*/

CedarDump::CedarDump()
{
  suspended=0;
  if (counter++ == 0) 
    {
      char log_name [255]="CEDAR_API_Messages_dumped";
#ifndef __STRICT_ANSI__
      // We get try to get the process id
      int process_id=getpid();
      /*
        When the API is not ANSI every instance can have its own log name and 
        we guarantee is unique because we build the string with current the process_id.
      */
      strcat(log_name,"_");
      char process_id_as_string [30]="\0";
      CedarStringConversions::ltoa(process_id, process_id_as_string, 10);
      strcat(log_name,process_id_as_string);
#endif
      strcat (log_name,".log");
      file_is_open=0;
      file_buffer.open (log_name, ios::out);
      // If we can not open a file handler there is not way to route the data, call error handler.
      if (!file_buffer)
	CedarErrorHandler::errorT(CEDARDUMP__EXIT__FATAL_OPENING_FILE_BUFFER,"s",CEDARDUMP__FATAL__OPENING_FILE_BUFFER);
      else 
	file_is_open=1;
      file_buffer<<CEDARDUMP__MSG__LOG_HEADER;
      dump_time(1);
#ifndef __STRICT_ANSI__
      file_buffer<<CEDARDUMP__MSG__PROCESS_ID<<process_id<<endl;
#endif
      puthead(CEDARDUMP__PROTOTYPE__1);
      file_buffer<<CEDARDUMP__MSG__CONSTRUCTING;
      puttail(CEDARDUMP__PROTOTYPE__1);
    }
}

CedarDump:: ~CedarDump()
{
 if (--counter == 0)
    {
      // The destructor closes the log identitying itself and dumping the current time.
      puthead(CEDARDUMP__PROTOTYPE__3);
      file_buffer<<CEDARDUMP__MSG__DESTRUCTING;
      puttail(CEDARDUMP__PROTOTYPE__3);
      file_buffer<<CEDARDUMP__MSG__LOG_TAIL;
      dump_time(1);
      if (file_is_open)
	{
	  file_buffer.close();
	  file_is_open=0;
	}
    }
}

/* 
   The member functions puthead and puttail expect to receive the full prototype (as a string)
   that identifys the function that is dumping. They provide a nice way to wrap messages between
   BEGIN... END... areas that are visually easier to recognize
*/

void CedarDump::puthead (const string &ptr) const
{
  if (!suspended)
    {
      file_buffer<<endl<<CEDARDUMP__MSG__HEADER_MESSAGE<<ptr;
      file_buffer<<CEDARDUMP__MSG__CURRENT_TIME;
      dump_time(0);
    }
}

void CedarDump::puttail (const string &ptr) const
{
  if (!suspended)
    file_buffer<<CEDARDUMP__MSG__TAIL_MESSAGE<<ptr<<endl;
}

/*
  dump_time helps all the other member functions to dump a preformated date-time identification message
  dump_time is based on routines from <time.h>
*/

void CedarDump::dump_time(int mode) const
{
  const time_t sctime=time(NULL);
  const struct tm *sttime=localtime(&sctime); 
  /* 
     After the local time has been loaded into an struct tm 
     (check <time.h> if you do not know what an struct tm is)
     We can either log the full zone, date and time if mode is 1
     or just the time in hours, minutes and seconds if mode is 0
  */
  if (mode==1) 
    {
      char zone_name[10];
      strftime(zone_name, sizeof(zone_name), "%Z", sttime);
      file_buffer<<zone_name<<" "<<asctime(sttime);
    }
  else if (mode==0)
    {
      char timeonly[10];
      strftime(timeonly, sizeof(timeonly), "%X", sttime);
      file_buffer<<timeonly<<endl;
    }
}

void CedarDump::suspend()
{
  suspended=1;
}

void CedarDump::resume()
{
  suspended=0;
}

CedarDump& CedarDump::operator<<(string &val) 
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

CedarDump& CedarDump::operator<<(int val) 
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

CedarDump& CedarDump::operator<<(char val) 
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

CedarDump& CedarDump::operator<<(long val) 
{
  if (!suspended)
      file_buffer<<val;
  return *this;
}

CedarDump& CedarDump::operator<<(double val) 
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

CedarDump& CedarDump::operator<<(bit val) 
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

CedarDump& CedarDump::operator<<(byte val) 
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

CedarDump& CedarDump::operator<<(field val) 
{
  if (!suspended)
      file_buffer<<val;
  return *this;
}

CedarDump& CedarDump::operator<<(date_field val) 
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

CedarDump& CedarDump::operator<<(p_ostream_manipulator val) 
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}
CedarDump& CedarDump::operator<<(p_ios_manipulator val) 
{ 
  if (!suspended)
    file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(const string &val) const
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(int val) const
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(char val) const
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(long val) const
{
  if (!suspended)
      file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(double val) const
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(bit val) const
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(byte val) const
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(field val) const
{
  if (!suspended)
      file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(date_field val) const
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}

const CedarDump& CedarDump::operator<<(p_ostream_manipulator val) const
{
  if (!suspended)
    file_buffer<<val;
  return *this;
}
const CedarDump& CedarDump::operator<<(p_ios_manipulator val) const
{ 
  if (!suspended)
    file_buffer<<val;
  return *this;
}

CedarDump &
CedarDump::Dumper()
{
    if( _instance == 0 )
    {
	_instance = new CedarDump ;
    }
    return *_instance ;
}

