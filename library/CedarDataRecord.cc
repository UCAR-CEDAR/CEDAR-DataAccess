/*******************************************************************
 * CLASS CedarDataRecord - Definition
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
#include "CedarErrors.h"
#include "CedarDataRecord.h"
#ifdef LOGGING_WITH_CEDARDUMP
#include "CedarDump.h"
#endif

using std::ostream ;
using std::endl ;

CedarDataRecord::CedarDataRecord():data_record_data(12288,4096)
{
  type=1;
  LPROL=0;
  JPAR=0;
  MPAR=0;
  NROW=0;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARDATARECORD__PROTOTYPE__1);
  CedarDump::Dumper()<<CEDARDATARECORD__MSG__CONSTRUCTED;
  CedarDump::Dumper().puttail(CEDARDATARECORD__PROTOTYPE__1);
#endif
}

CedarDataRecord::~CedarDataRecord()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARDATARECORD__PROTOTYPE__2);
  CedarDump::Dumper()<<CEDARDATARECORD__MSG__DESTRUCTED;
  CedarDump::Dumper().puttail(CEDARDATARECORD__PROTOTYPE__2);
#endif
}

void CedarDataRecord::save_data_buffer(streambuf *out) const
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARDATARECORD__PROTOTYPE__3);
  CedarDump::Dumper()<<CEDARDATARECORD__MSG__NUMBER_FIELDS_DATA<<(JPAR*2+MPAR+MPAR*NROW)<<ENDL;
#endif
  ostream fl(out);
  int k;
  fl<<"-----1D Array follows-----\n";
  for (k=0; k<JPAR; k++)
    {
      fl<<data_record_data[k]; 
      fl<<" ";
    }
  fl<<endl;
  for (k=JPAR; k<JPAR*2; k++)
    {
      fl<<data_record_data[k]; 
      fl<<" ";
    }
  fl<<endl; 
  fl<<"-----2D Array follows-----\n";
  for (k=JPAR*2; k<JPAR*2+MPAR; k++)
    {
      fl<<data_record_data[k]; 
      fl<<" ";
    }
  fl<<endl;
  for (int w=1; w<=NROW; w++)
    {
      for (k=(JPAR*2+MPAR*w); k<(JPAR*2+(w+1)*MPAR); k++)
	{
	  fl<<data_record_data[k]; 
	  fl<<" ";
	}
      fl<<endl;
    }
  fl<<endl;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puttail(CEDARDATARECORD__PROTOTYPE__3);
#endif
}

void CedarDataRecord::save_prologue(streambuf *out) const
{
  ostream fl(out);
  CedarLogicalRecord::save_prologue(out);
  fl<<LPROL<<"\t"<<JPAR<<"\t"<<MPAR<<"\t"<<NROW<<endl;
}

int CedarDataRecord::load_JPAR_data(vector<short int> &pt)
{
  int k,id;
  for (k=JPAR; k<JPAR*2; k++)
    {
      id=k-JPAR;
      pt[id]=data_record_data[k]; 
    }
  return 1;
}

int CedarDataRecord::load_JPAR_vars(vector<short int> &pt)
{
  int k;
  for (k=0; k<JPAR; k++)
    {
      pt[k]=data_record_data[k]; 
    }
  return 1;
}

int CedarDataRecord::load_MPAR_data(vector<short int> &pt)
{
  int i=0;
  int k,w;
  for (w=1; w<=NROW; w++)
    {
      for (k=(JPAR*2+MPAR*w); k<(JPAR*2+(w+1)*MPAR); k++)
	{
	  pt[i]=data_record_data[k]; 
	  i++;
	}
    }
  return 1;
}

int CedarDataRecord::load_MPAR_vars(vector<short int> &pt)
{
  int i=0;
  int k;
  for (k=JPAR*2; k<JPAR*2+MPAR; k++)
    {
      pt[i]=data_record_data[k]; 
      i++;
    }
  return 1;
}

