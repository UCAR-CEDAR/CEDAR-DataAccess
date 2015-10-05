/*******************************************************************
 * CLASS CedarRecordType - Declaration
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

#ifndef CedarRecordType_h_
#define CedarRecordType_h_ 1

#include "CedarDataTypes.h"

/// Class for record types.

/**
   Encapsulates data and behavior for the concept of a "Record Type" and the CEDAR API.
   A record type in the CEDAR API is a unique object define by a unique combination of
   a kinst (instrument) and a kindat.
*/
class CedarRecordType
{
  /// kinst for this record type.
  field my_kinst;
  /// kindat for this record type.
  field my_kindat;
public:
  /// Default constructor.
  CedarRecordType(field ki=0, field kd=0);
  /**
     Overloaded == operator.
     @return 1 is the objects are equal, 0 otherwise.
  */
  int operator==(const CedarRecordType &x);
  /// Returns the kindat for this object.
  field get_kindat(){return my_kindat;}
  /// Returns the kinst for this object.
  field get_kinst(){return my_kinst;}
  /// 
  void set_kinst(const field &f){my_kinst=f;}
  ///
  void set_kindat(const field &f){my_kindat=f;}
};

#endif // CedarRecordType_h_


