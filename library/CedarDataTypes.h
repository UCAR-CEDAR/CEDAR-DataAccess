/*******************************************************************
 * Declaration of basic Cedar Data Types
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

#ifndef CedarDataTypes_h_
#define CedarDataTypes_h_ 1

/** 
  Definition of the data type byte.
  
  A byte represents one unit of data equivalent to 8 bits. 
  
  For the CEDAR API to work the data type "byte" MUST be one byte,
  that is sizeof (byte) = 1 byte = 8 bits. 

 */

typedef unsigned char byte;


/** 
  Definition of the data type field.

  A field represents a signed integer number and is expected to be 
  two bytes long, that is sizeof (byte) = 2 byte = 16 bits.

  Bit order:  bits 8-15 are in byte O and bits 0-7 are in byte 1 like this;
  \begin{description}
  \item[1.-] byte 0 the left most and byte 1 the right most.
  \item[2.-] Bit order : byte 0 + byte 1 = 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
  \end{description}

  If you compiler for your OS does not create field two bytes long or the 
  byte order is not as expected the CEDAR-API will not work correctly.

 */

typedef short int field;

/** 
 Definition of the data type date_field.
 
 A date_field is like field  but it is unsigned that is, it can not be negative.
 
 The data type date_field exist because values for beginning or end dates 
 (IB??? and IE???) for cedar logical records can not be negative.
 
 */

typedef unsigned short int  date_field;

/**
  Definition of the data type CedarLogicalRecordPrologue_TAG.
  
  CedarLogicalRecordPrologue_TAG represents the basic prologue for Cedar Logical Records.

  The structure contains:
  \begin{description}
  \item[1.-] LTOT;   Length of the record. The units for LTOT depend is the record is either 
  header, catalog or data. 
  \item[2.-] KREC;   Kind of record. It can be 1002 for binary data, 2001 for binary catalog
  or 3002 for binary header.
  \item[3.-] KINST;  Instrument code for the experiment.
  \item[4.-] KINDAT; Kind of data code for header and data records or code to indicate
  experimental mode employed for catalog records 
  \item[5.-] IBYRT;  Beginning year
  \item[6.-] IBDTT;  Beginning month day
  \item[7.-] IBHMT;  Beginning hour minute
  \item[8.-] IBCST;  Beginning second centisecond
  \item[9.-] IEYRT;  Ending year
  \item[10.-] IEDTT;  Ending month day
  \item[11.-] IEHMT;  Ending hour minute
  \item[12.-] IECST;  Ending second centisecond
  \end{description}
  
*/

struct CedarLogicalRecordPrologue_TAG
{
  field LTOT;  
  field KREC;  
  field KINST; 
  field KINDAT;
  date_field IBYRT; 
  date_field IBDTT; 
  date_field IBHMT; 
  date_field IBCST;
  date_field IEYRT;
  date_field IEDTT;
  date_field IEHMT;
  date_field IECST;
};

/**
  Use CedarLogicalRecordPrologue as a data type instead of struct CedarLogicalRecordPrologue_TAG. 
  It is defined as: typedef struct CedarLogicalRecordPrologue_TAG CedarLogicalRecordPrologue.
 */

typedef struct CedarLogicalRecordPrologue_TAG CedarLogicalRecordPrologue;

#endif // CedarDataTypes_h_
