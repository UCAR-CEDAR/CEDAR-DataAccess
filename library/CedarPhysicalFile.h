/*******************************************************************
 * CLASS CedarPhysicalFile - Declaration
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

#ifndef CedarPhysicalFile_h_
#define CedarPhysicalFile_h_ 1

/**
   MAXFILENAME defines the maximum length allowed to file's name as 255 characters. 
   The value used here restricts the length to the limit of some BSD versions of UNIX
   Check the documentation for your OS to modify this value
*/
#define MAXFILENAME 255

class CedarGroup;
class CedarLogicalRecord;

/**
   Represents the abstract interface to File that contains Cedar data.
 */
class CedarPhysicalFile
{
  int type;

public:
  CedarPhysicalFile(){type=0;}
  ///
  virtual ~CedarPhysicalFile() {};
  
  /// Associates the object with a CBF file.
  virtual void open_file(const char *file_name)=0;

  /**
   *@name Sequencial access.
   * Documentation not ready.
   */
  //@{
    /**
     * Takes as a parameter a reference to a CedarBlock object and loads into it a block of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual const CedarLogicalRecord* get_first_logical_record ()=0;
    /**
     * Takes as a parameter a reference to a CedarBlock object and loads into it a block of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual const CedarLogicalRecord* get_next_logical_record()=0;
    /**
     * Takes as a parameter a reference to a CedarGroup object and loads into it a group of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual int get_first_CedarGroup (CedarGroup &)=0;
    /**
     * Takes as a parameter a refernce to a CedarGroup object and loads into it a group of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual int get_next_CedarGroup  (CedarGroup &)=0;
  
  //@}

  /// Returns 1 when the end of the data set is reached, else returns 0.
  virtual int end_dataset()=0;
  ///
  virtual void rewind()=0;

};

#endif // CedarPhysicalFile_h_
