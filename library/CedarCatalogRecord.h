/*******************************************************************
 * CLASS CedarCatalogRecord - Declaration
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

#ifndef CedarCatalogRecord_h_
#define CedarCatalogRecord_h_ 1

#include "CedarLogicalRecord.h"

/**
 * Abstraction for the concept of a Catalog record in the CEDAR database.
 * Documentation not ready.
 */

class CedarCatalogRecord :public CedarLogicalRecord
{
  /// Buffer to contain data (char type) for this Cedar Catalog Record.
  CedarArray<char> catalog_record_data;

  friend class CedarLogicalRecordBuilder;
  friend class CedarBlock;

public:
  CedarCatalogRecord();
  virtual ~CedarCatalogRecord();

  /// Overrides the virtual function save_prologue as defined in CedarLogicalRecord.
  virtual void save_prologue(streambuf *out) const;

  /// Overrides the pure virtual function save_data_buffer as defined in CedarLogicalRecord.
  virtual void save_data_buffer(streambuf *out) const;
};

#endif // CedarCatalogRecord_h_

