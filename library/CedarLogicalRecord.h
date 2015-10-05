/*******************************************************************
 * CLASS CedarLogicalRecord - Declaration
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

#ifndef CedarLogicalRecord_h_
#define CedarLogicalRecord_h_ 1

#include <iostream>

using std::streambuf ;

#include "CedarArray.h"
#include "CedarDataTypes.h"
#include "CedarDate.h"

/**
 * Abstraction for the concept of a logical record in the CEDAR database.
 * Documentation not ready.
 */

class CedarLogicalRecord
{
protected:
  /**
   * Common prologue for all kind of logical records. 
   * See CedarLogicalRecordPrologue_TAG in CedarDataTypes for more information.
   */
  CedarLogicalRecordPrologue prologue;
  /**
   * Type of record. 
   * This value is set at construction time.
   * For pure virtual logical record is 0, for data is 1 for catalog is 2 and for header 3.
   */
  int type;

  friend class CedarLogicalRecordBuilder;
  friend class CedarBlock;

public:
  CedarLogicalRecord();
  virtual ~CedarLogicalRecord();

  /// Returns value of protected member "type" to indicate the type of record.
  int get_type() const {return type;}

  /// Returns the length of the record by returning prologue member LTOT. 
  int get_record_length() const {return prologue.LTOT;}

  ///Returns the kind of the record by returning prologue member KREC.
  int get_record_kind() const {return prologue.KREC;}

  /// Returns the kind of the record by returning prologue member KINST.
  int get_record_kind_instrument() const {return prologue.KINST;}

  /// Returns the kind of data of record by returning prologue member KINDAT.
  int get_record_kind_data() const {return prologue.KINDAT;}

  /**
   * Loads the begging date of the record prologue (members IB???) in the referenced parameter CedarDate object.
   * Returns 1 if the CedarDate object was loaded with a valid date, else returs 0.
   */
  int get_record_begin_date(CedarDate& dat) const {return dat.set_date(prologue.IBYRT,prologue.IBDTT, prologue.IBHMT,prologue.IBCST);}

 /**
   * Loads the ending date of the record prologue (members IE???) in the referenced parameter CedarDate object.
   * Returns 1 if the CedarDate object was loaded with a valid date, else returs 0.
   */
  int get_record_end_date(CedarDate& dat) const {return dat.set_date(prologue.IEYRT,prologue.IEDTT, prologue.IEHMT,prologue.IECST);}

  /** 
   * Function to validate record by criteria established using parameters field, field, CedarDate and CedarDate.
   * Documentation not ready.
   */
  int validate_record(field, field, CedarDate &, CedarDate &) const;

  /**
   * Writes a pre-formatted prologue header in a text file.
   * Documentation not ready.
   * fl object must have been opened for text operations.
   */
  void save_prologue_header(streambuf *out) const;

  /**
   * Writes the prologue for the record pre-formatted in a text file.
   * Documentation not ready.
   * fl object must have been opened for text operations.
   */
  virtual void save_prologue(streambuf *out) const;

  /**
   * Pure virtual function that gets implemented by child classes.
   * Its objective is to write to a text file the data contained
   * in the data buffer for the record.
   * Documentation not ready.
   */
  virtual void save_data_buffer(streambuf *out) const =0;
};

#endif // CedarLogicalRecord_h_

