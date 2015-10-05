/*******************************************************************
 * CLASS CedarFile - Declaration
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

#ifndef CedarFile_h_
#define CedarFile_h_ 1

#include "CedarCrayServices.h"
#include "CedarPhysicalFile.h"
#include "CedarErrorHandler.h"

/// Defines that an object of the class CedarFile must do check sum on the blocks it returns.
#define CEDAR_DO_CHECK_SUM 1

// Possible formats in which Cedar physical records can be storaged.
#define CEDARFILE_ABSTRACT_FACTORY 1
#define CRAY_BLOCKING_FORMAT 2
#define MADRIGAL_FORMAT 3
#define CEDARFILE_UNKNOWN_FORMAT 4



/**
   Abstract Factory.
 */


class CedarFile 
{
  ///
  CedarPhysicalFile *f;
  ///
  void determine_file(const char *file_name);
  ///
  int with_check_sum;
  
public: 

  /// Default constructor.
  CedarFile(int check_blocks=0, int format=CEDARFILE_ABSTRACT_FACTORY);
 
  
  /// Destructor.
  ~CedarFile();
  
  /// Associates the object with a CBF file.
  void open_file(const char *file_name);
  
  
  ///
  const CedarLogicalRecord* get_first_logical_record()
  {
    if( !f )
	CedarErrorHandler::errorT(CEDARFILE__EXIT__FILE_NOT_OPEN,"s",CEDARFILE__FATAL__FILE_NOT_OPEN);
    return f->get_first_logical_record();
  }
  
  ///
  const CedarLogicalRecord* get_next_logical_record()
  {
    if( !f )
	CedarErrorHandler::errorT(CEDARFILE__EXIT__FILE_NOT_OPEN,"s",CEDARFILE__FATAL__FILE_NOT_OPEN);
    return f->get_next_logical_record();
  }
  
  ///
  int get_first_CedarGroup (CedarGroup &g)
  {
    if( !f )
	CedarErrorHandler::errorT(CEDARFILE__EXIT__FILE_NOT_OPEN,"s",CEDARFILE__FATAL__FILE_NOT_OPEN);
    return f->get_first_CedarGroup(g);
  }
  
  ///
  int get_next_CedarGroup  (CedarGroup &g)
  {
    if( !f )
	CedarErrorHandler::errorT(CEDARFILE__EXIT__FILE_NOT_OPEN,"s",CEDARFILE__FATAL__FILE_NOT_OPEN);
    return f->get_next_CedarGroup(g);
  }
  
  /// Returns 1 when the end of the data set is reached, else returns 0.
  int end_dataset() 
  {
    if( !f )
	CedarErrorHandler::errorT(CEDARFILE__EXIT__FILE_NOT_OPEN,"s",CEDARFILE__FATAL__FILE_NOT_OPEN);
    return f->end_dataset();
  }

};


#endif // CedarFile_h_

