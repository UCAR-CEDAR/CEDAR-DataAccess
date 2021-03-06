/*******************************************************************
 * CLASS CedarHeaderRecord - Definition
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
#include "CedarHeaderRecord.h"
#ifdef LOGGING_WITH_CEDARDUMP
#include "CedarDump.h"
#endif

using std::ostream ;
using std::endl ;

CedarHeaderRecord::CedarHeaderRecord():header_record_data(8192,4096)
{
  type=3;
  LPROL=0;
  JPAR=0;
  MPAR=0;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARHEADERRECORD__PROTOTYPE__1);
  CedarDump::Dumper()<<CEDARHEADERRECORD__MSG__CONSTRUCTED;
  CedarDump::Dumper().puttail(CEDARHEADERRECORD__PROTOTYPE__1);
#endif
}

CedarHeaderRecord::~CedarHeaderRecord()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARHEADERRECORD__PROTOTYPE__2);
  CedarDump::Dumper()<<CEDARHEADERRECORD__MSG__DESTRUCTED;
  CedarDump::Dumper().puttail(CEDARHEADERRECORD__PROTOTYPE__2);
#endif
}

void CedarHeaderRecord::save_data_buffer(streambuf *out) const
{
  ostream fl(out);
  int total_byte_length=(prologue.LTOT*2)-80;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARHEADERRECORD__PROTOTYPE__3);
  CedarDump::Dumper()<<CEDARHEADERRECORD__MSG__NUMBER_BYTES_DATA<<total_byte_length<<ENDL;
#endif
  for (int i=0, j=0; i<total_byte_length; i++, j++)
    {
      fl<<header_record_data[i];
      if (j==79)
	{
	  fl<<endl;
	  j=-1;
	}
    }
  fl<<endl;  
#ifdef LOGGING_WITH_CEDARDUMP
    CedarDump::Dumper().puttail(CEDARHEADERRECORD__PROTOTYPE__3);
#endif
}

void CedarHeaderRecord::save_prologue(streambuf *out) const
{
  ostream fl(out);
  CedarLogicalRecord::save_prologue(out);
  fl<<LPROL<<"\t"<<JPAR<<"\t"<<MPAR<<"\t"<<"N/A"<<endl;
}

