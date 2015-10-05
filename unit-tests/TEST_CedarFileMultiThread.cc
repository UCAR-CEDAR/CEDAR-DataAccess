/*******************************************************************
 * TEST CedarFileMultiThread
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

#include <iostream>

using std::cout ;
using std::endl ;

#include "CedarFile.h"
#include "CedarException.h"

void dummy0()
{
  CedarFile f;
  f.open_file("/usr/madrigal/files/stage/mfp890505a.cbf");
  f.get_next_logical_record();
}

void dummy()
{
  cout<<"Trying multi-thread"<<endl;
  CedarFile f;
  f.open_file("/usr/madrigal/files/stage/whf980924a.cbf");
  f.get_first_logical_record();
  struct timespec tv;
  tv.tv_sec=0;
  tv.tv_nsec=2;
  //nanosleep(&tv,0);
  //sleep(3);
  f.get_next_logical_record();
  cout<<"Returning"<<endl;
}

int
main()
{
  try
    {
      dummy0();
    }
  catch(CedarException &e)
    {
      cout<<e.get_description()<<endl;
    }
  try
    {
      dummy();
    }
  catch(CedarException &e)
    {
      cout<<e.get_description()<<endl;
    }
  catch(...)
    {
      cout<<"??????"<<endl;
    }

}
