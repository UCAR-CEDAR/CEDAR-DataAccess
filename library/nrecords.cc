/*******************************************************************
 * PROGRAM nrecords
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

#include <sys/types.h>
#include <ctime>
#include <cstdlib>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <iostream>

#include "CedarFile.h"
#include "CedarException.h"
#include "CedarVersion.h"
#include "CedarString.h"
#include "CedarLogicalRecord.h"

using std::cout ;
using std::endl ;
using std::cerr ;

//Functions declarations

const char* NameProgram=0;

void
show_version()
{
    cout << NameProgram << " using libraryCedar: "
         << CedarVersion::get_version_number() << endl
	 << CedarVersion::get_version_info() << endl ;
    exit( 0 ) ;
}

void
show_usage()
{
    cout << NameProgram << " -f [FILE] -a -s -v" << endl ;
    cout << "-f flag is mandatory, FILE is the file to load" << endl ;
    cout << "-a flag is optional, it indicates that all logical records"
         << " should be counted." << endl ;
    cout << "-s flag is optional, it sets the checksum per block to be true,"
         << " thus is slower but safer." << endl ;
    cout << "-v flag shows the version. All other flags are ignored." << endl ;
    exit( 1 ) ;
}

inline int
execute_request(const char* f, bool all_records, bool check_sum)
{
  register int nrecords=0;
  clock();
  time_t t1=time(NULL);
  try
    {
      CedarFile file(check_sum, CRAY_BLOCKING_FORMAT);
      file.open_file (f);
      const CedarLogicalRecord* lr=file.get_first_logical_record();
      if(lr)
	{
	  if (lr)
	    {
	      if (all_records)
		nrecords++;
	      else
		{
		  switch (lr->get_type())
		    {
		    case 1:
		      nrecords++;
		      break;
		    default:
		      break;
		    }
		}
	    }
	  while (!file.end_dataset())
	    {
	      lr=file.get_next_logical_record();
	      if(lr) 
		{
		  if (all_records)
		    nrecords++;
		  else
		    {
		      switch (lr->get_type())
			{
			case 1:
			  nrecords++;
			  break;
			default:
			  break;
			}
		    }
		}
	    }
	  cout<<nrecords<<" (Total time "<<time(NULL)-t1<<" sec. CPU usage "<<clock()<<" microsec.)"<<endl;
	  return 0;
	}
      else
	cout<<NameProgram<<": can not connect to file "<<f<<endl;
      
    }
  catch (CedarException &ex)
    {
      cout<<"Reporting exception from Cedar++"<<endl;
      cout<<ex.get_description()<<endl;
      cerr<<NameProgram<<": failing with status "<<ex.get_error_code()<<" on "<<f<<endl;
      return ex.get_error_code();
    }
  catch(...)
    {
      cout<<NameProgram<<": reporting unknown  exception, exiting program."<<endl;
      return 1;
    }
  return 0;
}



int main(int argc, char *argv[])
{
  NameProgram=argv[0];

  bool all_logical_record(false);
  bool got_file(false);
  int check_sum=0;
  
  const char *file=0;

  int c;

  while ((c=getopt(argc,argv,"svaf:"))!=EOF)
    {
      switch (c)
	{
	case 'v':
	  show_version();
	  break;
	case 'a':
	  all_logical_record=true;
	  break;
	case 'f':
	  file=optarg;
	  got_file=true;
	  break;
	case 's':
	  check_sum=CEDAR_DO_CHECK_SUM;
	  break;
	case '?':
	  show_usage();
	  break;
	}
    }
  if (got_file)
    return execute_request(file, all_logical_record, check_sum);
  else
    {
      show_usage();
      return 1;
    }
}
