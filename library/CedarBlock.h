/*******************************************************************
 * CLASS CedarBlock - Declaration
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

#ifndef CedarBlock_h_
#define CedarBlock_h_ 1

#include "CedarCatalogRecord.h"
#include "CedarDataRecord.h"
#include "CedarHeaderRecord.h"

/**
 * Data and block behavior for the CEDAR API.
 * Documentation not ready.
 *
 */

class CedarBlock
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
  /// Indicates the current position of the byte being used from the "Internal data buffer"
  int crData_marker;  
  /// Internal data buffer
  CedarArray<byte> crData;        
  /// Amount of meaningful bytes loaded in the "Internal data buffer" 
  int value;
  /**
   * We allow the CedarFile class to be "friend" so data can be easily extracted from CBF files
   * to the internal data buffer of this CedarBlock.
   */
  friend class CedarCrayBlockingFormat;
  /**
   * Return the amount of bytes loaded into the internal data buffer as defined by the first two
   * bytes of a CEDAR block.
   */ 
  /* 
   * get_block_length calculates and returns the length (in fields) of the physical record as the
   * integer value for the first two bytes (first two bytes=first field) of the array.
   * This value includes the lenght for all the logical records plus the last field (the checksum)
   * plus the first field (the block length). Remember, fields here are define as two bytes.
   */
  int get_block_length()
  {
    return build_field(0);
  }

  /**
   * Builds a field value by using the byte in the position defined by the parameter 
   * and the byte in position + 1 from the internal data buffer.
   * Returns the field value.
   */
  /*
   * As define in "CedarDataTypes.h" a field is a short integer
   * For the following tested systems:
   * SunOS hao 5.5.1 Generic_103640-18 sun4u sparc SUNW,Ultra-2
   * SunOS jawa 5.5.1 Generic_103640-18 sun4m sparc SUNW,SPARCstation-20
   * SunOS cedar 5.5.1 Generic_103640-18 sun4m sparc SUNW,SPARCstation-5
   * a short integer is 2 bytes long. 
   * The bits 8-15 are in the byte 0, the bits 0-7 are in the byte 1. 
   * The build_field function takes the byte in position pos from the CedarArray
   * of bytes (crData) as the high byte and the next (pos+1) as the low byte
   * In other systems where a short int is not 2 bytes, the function WILL NOT WORK
   * you need to redefined field as any datatype that is 2 bytes in your OS.
   * RETURN VALUE: the integer built with two bytes plus its sign 
   */
  field build_field(int pos)
  {
    register field higher_byte=crData[pos]<<8;
    register field lower_byte=crData[pos+1];
    return (higher_byte|lower_byte);
  }
  /**
   * Executes a check sum for the internal data buffer as define in the CEDAR database format.
   * Returns 0 is the check sum is not OK, returns 1 if the check sum is OK
   */
  int do_block_checksum();
  /// Loads the record's prologue with data from the internal data buffer.
  void build_record_prologue(int kind_record);
  /// When the record is Data, loads the extended values for its prologue.
  void get_data_extended_prologue();
  /// When the record is Header, loads the extended values for its prologue.
  void get_header_extended_prologue();     
  /// Loads the buffer for the Data record with the data from the internal data buffer.
  void load_data_record_data();
  /// Loads the buffer for the Catalog record with the data from the internal data buffer.
  void load_catalog_record_data();
  /// Loads the buffer for the Header record with the data from the internal data buffer.
  void load_header_record_data();
public:  
  /// Default constructor.
  CedarBlock();
  ~CedarBlock();
  /**
   *@name Sequencial access.
   * Documentation not ready.
   *
   */
  //@{
     /// Return a pointer to the first Logical record in the internal data buffer.
         const CedarLogicalRecord* get_first_record();
     /// Return a pointer to the next Logical record in the internal data buffer.
         const CedarLogicalRecord* get_next_record();
  //@}
  /// Flushes the internal data buffer.
  void flush();
};

#endif // CedarBlock_h_


