/*******************************************************************
 * CLASS CedarMadrigalFormat - Declaration
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

#ifndef CedarMadrigalFormat_h_
#define CedarMadrigalFormat_h_ 1

#include <fstream>

using std::ifstream ;

#include "CedarPhysicalFile.h"
#include "CedarLogicalRecordBuilder.h"

#define MADRIGAL_PHYSICAL_RECORD_LENGTH 13440

/**
   Implementation of Cedar Physical file for Madrigal format.
 */

class CedarMadrigalFormat : public CedarPhysicalFile
{
  CedarLogicalRecordBuilder record;
  ///
  int total_number_of_significant_bytes;
  ///
  int first_word_of_the_first_logical_record_start;
  ///
  int first_word_of_the_last_logical_record_start;
  

  ///
  int end_of_dataset;
  ///
  char name [MAXFILENAME];
  ///
  int has_name;
  /// File handler and stream for the connection.
  ifstream os;
  ///
  int count;
  ///
  int log_counter;
  
  
  ///
  int check_sum_on_blocks;
  ///
  byte buf [MADRIGAL_PHYSICAL_RECORD_LENGTH];
  ///
  int buf_marker;
  

  ///
  field build_word(int pos)
  {
    return ( (buf[pos]<<8) | (buf[pos+1]) );
  }
  ///
  int do_checksum();
  ///
  int load_madrigal_buffer();
  ///
  const CedarLogicalRecord* get_first_record();
  ///
  const CedarLogicalRecord* get_next_record();
  
public:

  /// Default constructor.
  CedarMadrigalFormat(int check_blocks);
  /// Destructor.
  ~CedarMadrigalFormat();

  /// Associates the object with a CBF file.
  virtual void open_file(const char *file_name);

  /**
   *@name Sequencial access.
   * Documentation not ready.
   */
  //@{
    /**
     * Takes as a parameter a reference to a CedarBlock object and loads into it a block of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual const CedarLogicalRecord* get_first_logical_record();
    /**
     * Takes as a parameter a reference to a CedarBlock object and loads into it a block of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
	  virtual const CedarLogicalRecord* get_next_logical_record();
    /**
     * Takes as a parameter a reference to a CedarGroup object and loads into it a group of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual int get_first_CedarGroup (CedarGroup &);
    /**
     * Takes as a parameter a refernce to a CedarGroup object and loads into it a group of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual int get_next_CedarGroup  (CedarGroup &);
  
  //@}

  /// Returns 1 when the end of the data set is reached, else returns 0.
  virtual int end_dataset() {return end_of_dataset;}
  ///
  virtual void rewind();
};


#endif // 
