/*******************************************************************
 * CLASS CedarDataRecord - Declaration
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

#ifndef CedarDataRecord_h_
#define CedarDataRecord_h_ 1

#include <vector>

using std::vector ;

#include "CedarLogicalRecord.h"

/**
 * Abstraction for the concept of a Data record in the CEDAR database.
 * Documentation not ready.
 */

class CedarDataRecord :public CedarLogicalRecord
{
  /// Buffer to contain data (field type) for this Cedar Data Record.
  CedarArray<field> data_record_data;
  /**
   * Extended prologue in 13th position, unique for Cedar Data Record. 
   * Indicates the length of the prologue for this data record.
   */  
  field LPROL;
  /**
   * Extended prologue in 14th position, unique for Cedar Data Record. 
   * Indicates the number of single value parameters for this data record.
   */
  field JPAR;
  /**
   * Extended prologue in 15th position, unique for Cedar Data Record.
   * Indicates the number of multiple value parameters for this data record.
   */
  field MPAR;
  /**
   * Extended prologue in 16th position, unique for Cedar Data Record.
   * Indicates the number of rows for multiple value parameters for this data record.
   */
  field NROW;
  ///
  friend class CedarLogicalRecordBuilder;
  ///
  friend class CedarBlock;

public:

  /// Default Constructor.
  CedarDataRecord();
  /// Destructor
  virtual ~CedarDataRecord();
  /// Overrides the virtual function save_prologue as defined in CedarLogicalRecord.
  void save_prologue(streambuf *out) const;
  /// Overrides the pure virtual function save_data_buffer as defined in CedarLogicalRecord.
  void save_data_buffer(streambuf *out) const;
  /// Gets the JPAR value for this CedarDataRecord.
  field get_jpar(){return JPAR;}
  /// Gets the MPAR value for this CedarDataRecord.
  field get_mpar(){return MPAR;}	
  /// Gets the NROW value for this CedarDataRecord.
  field get_nrows(){return NROW;}	   
  /// Loads the JPAR data into pt buffer.
  int load_JPAR_data(vector<short int> &pt);
  /// Loads the JPAR vars into pt buffer.
  int load_JPAR_vars(vector<short int> &pt);
 /// Loads the MPAR data into pt buffer.
  int load_MPAR_data(vector<short int> &pt);
  /// Loads the MPAR vars into pt buffer.
  int load_MPAR_vars(vector<short int> &pt);
};

#endif // CedarDataRecord_h_
