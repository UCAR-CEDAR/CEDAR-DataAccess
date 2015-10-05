/*******************************************************************
 * CLASS CedarLogicalRecord - Definition
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

#include <iostream>

using std::ostream ;
using std::endl ;

#include "CedarConfig.h"
#include "CedarMessages.h"
#include "CedarErrors.h"
#include "CedarLogicalRecord.h"
#ifdef LOGGING_WITH_CEDARDUMP
#include "CedarDump.h"
#endif

CedarLogicalRecord::CedarLogicalRecord()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARLOGICALRECORD__PROTOTYPE__1);
  CedarDump::Dumper()<<CEDARLOGICALRECORD__MSG__CONSTRUCTED;
  CedarDump::Dumper().puttail(CEDARLOGICALRECORD__PROTOTYPE__1);
#endif
  // Initializes all data members to ZERO...
  type=0;
  prologue.LTOT=0; 
  prologue.KREC=0;  
  prologue.KINST=0; 
  prologue.KINDAT=0;
  prologue.IBYRT=0; 
  prologue.IBDTT=0; 
  prologue.IBHMT=0; 
  prologue.IBCST=0;
  prologue.IEYRT=0; 
  prologue.IEDTT=0;
  prologue.IEHMT=0;
  prologue.IECST=0;
}

CedarLogicalRecord::~CedarLogicalRecord()
{
#ifdef LOGGING_WITH_CEDARDUMP 
  CedarDump::Dumper().puthead(CEDARLOGICALRECORD__PROTOTYPE__2);
  CedarDump::Dumper()<<CEDARLOGICALRECORD__MSG__DESTRUCTED;
  CedarDump::Dumper().puttail(CEDARLOGICALRECORD__PROTOTYPE__2);
#endif
}

void CedarLogicalRecord::save_prologue_header(streambuf *out) const
{
  ostream fl(out);
  fl<<"LTOT"<<"\t"<<"KREC"<<"\t"<<"KINST"<<"\t"<<"KINDAT"<<"\t";
  fl<<"IBYRT"<<"\t"<<"IBDTT"<<"\t"<<"IBHMT"<<"\t"<<"IBCST"<<"\t";
  fl<<"IEYRT"<<"\t"<<"IEDTT"<<"\t"<<"IEHMT"<<"\t"<<"IECST"<<"\t";
  fl<<"LPROL"<<"\t"<<"JPAR"<<"\t"<<"MPAR"<<"\t"<<"NROW"<<endl;
}

void CedarLogicalRecord::save_prologue(streambuf *out) const
{
  ostream fl(out);
  fl<<prologue.LTOT<<"\t"; 
  fl<<prologue.KREC<<"\t";  
  fl<<prologue.KINST<<"\t"; 
  fl<<prologue.KINDAT<<"\t";
  fl<<prologue.IBYRT<<"\t"; 
  fl<<prologue.IBDTT<<"\t"; 
  fl<<prologue.IBHMT<<"\t"; 
  fl<<prologue.IBCST<<"\t";
  fl<<prologue.IEYRT<<"\t"; 
  fl<<prologue.IEDTT<<"\t";
  fl<<prologue.IEHMT<<"\t";
  fl<<prologue.IECST<<"\t";
}

int CedarLogicalRecord::validate_record(field kinst, field kindat, CedarDate &d1, CedarDate &d2) const
{
  // These CedarDate Objects represent the eight fields (I????) for beginning and ending dates on the prologue 
  CedarDate prologue_beginning_date, prologue_ending_date;
  // Flags to know if the restrictions are satisfy. Initial state FALSE=0 
  int instrument_valid=0, kind_of_data_valid=0, in_date_range_valid=0;
  /* 
   * Flags to know is the object is happy with the dates for this Logical Records prologue 
   * This will guarantee that there are not year's values like 126
   * or day's values like 111111 or hour_min's values like 13242363 or 
   * centisecond's values like 22222345. Remember that CedarDate::set_date will return 1 
   * if and only if the conditions for dates are satisfy by CedarValidDate member fuctions.
   */
  int is_beginning_date_valid=0, is_ending_date_valid=0;
  // Validating kind of instrument and kind of data 
  if (prologue.KINST==kinst)
    instrument_valid=1;  // Setting flag TRUE, the parameter received satisfy the KINST for the prologue of this logical record
  if(prologue.KINDAT==kindat)
    kind_of_data_valid=1;// Setting flag TRUE, the parameter received satisfy the KINDAT for the prologue of this logical record
  /*
   * Building object prologue_beginning_date
   */
  is_beginning_date_valid=prologue_beginning_date.set_date(prologue.IBYRT,prologue.IBDTT, prologue.IBHMT,prologue.IBCST);
  is_ending_date_valid=prologue_ending_date.set_date(prologue.IEYRT,prologue.IEDTT, prologue.IEHMT,prologue.IECST);
  if ((is_beginning_date_valid)&&(is_ending_date_valid))
    {
      // First we check that the prologue beginning date is before or equal the prologue ending date 
      if (prologue_beginning_date<=prologue_ending_date)
	{
	  /* 
	   * Now we check that the incoming dates as parameters are a valid range
	   * to contain the range [prologue_beginning_date,prologue_ending_date]
	   */
	  if (d1<d2)
	    {
	      // Finally we check that [prologue_beginning_date,prologue_ending_date] is contain in [d1,d2] 
	      if (!((prologue_ending_date<d1) || (prologue_beginning_date>d2)))
		in_date_range_valid=1; // We set the flag to TRUE because the date restriction is satisfied 
	    }
	}
    }
  // To calculate the return value we AND the restrictions flags 
  if ((instrument_valid) && (kind_of_data_valid) && (in_date_range_valid))
    return 1;
  else
    return 0;
}
