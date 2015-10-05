/*******************************************************************
 * CLASS CedarLogicalRecordBuilder - Declaration
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

#ifndef CedarLogicalRecordBuilder_h_
#define CedarLogicalRecordBuilder_h_ 1

#include "CedarDataTypes.h"
#include "CedarCatalogRecord.h"
#include "CedarDataRecord.h"
#include "CedarHeaderRecord.h"

class CedarLogicalRecordBuilder
{
  /**
   *@name Records contained in a CedarBlock.
   * A CedarBlock can contain header or data or catalog records
   * These data members can hold any of the possible records
   * existing in the "Internal data buffer"
   */
  //@{
    /// Header record area.
        CedarHeaderRecord the_header;   
    /// Catalog record area.       
	CedarCatalogRecord the_catalog; 
    /// Data record area.        
	CedarDataRecord the_data;
  //@}    
  
  ///
  int crData_marker;
  ///
  CedarArray<byte> crData;
  
  ///
  void build_record_prologue(int kind_record);
  ///
  void load_header_record_data();
  ///
  void load_catalog_record_data();
  ///
  void load_data_record_data();
  ///
  void get_data_extended_prologue();
  ///
  void get_header_extended_prologue();
  ///
  field build_field(int pos)
  {
    register field higher_byte=crData[pos]<<8;
    register field lower_byte=crData[pos+1];
    return (higher_byte|lower_byte);
  }
  
  friend class CedarBlock;
  friend class CedarMadrigalFormat;

public:
  ///
  CedarLogicalRecordBuilder();
  ///
  ~CedarLogicalRecordBuilder();
  ///
  const CedarLogicalRecord* get_record();
};

#endif // CedarLogicalRecordBuilder_h_