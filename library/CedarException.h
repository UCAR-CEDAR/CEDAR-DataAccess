/*******************************************************************
 * CLASS CedarException - Declaration
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

#ifndef CedarException_h_
#define CedarException_h_ 1

/// Exception transport mechanism in the CEDAR API.
class CedarException
{
  /// The error code.
  int _error_code;
  /// The description of the problem.
  char * _description;
public:
  /// Builds an object of this class (please notice there is not default constructor).
  CedarException(int i, const char *str);
  /// Copy constructor.
  CedarException(const CedarException &s);
  /// Overloaded = operator.
  CedarException& operator= (CedarException const &s);
  /// Destructor.
  ~CedarException();
  /// Returns the error code (See CedarErrors.h).
  int get_error_code(){return _error_code;}
  /// Returs an string (char*) with a description of the problem.
  const char*  get_description(){return _description;}
};


#endif // CedarException_h_
