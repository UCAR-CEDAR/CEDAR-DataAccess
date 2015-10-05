/*******************************************************************
 * CLASS CedarString - Declaration
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

#ifndef CedarString_h_
#define CedarString_h_ 1

#include <cstring>
#include <iostream>

using std::ostream ;
using std::istream ;

/**
 * Simple string class to handle string operations in Cedar++.
 * The idea of this class is not to replace the string class from stdc++
 * but rather offer backward compatibility with old compilers. It is well
 * known that the porting of a library is a difficult task because usually 
 * a programer "gets married" with its compiler without knowing so. Cedar++
 * trys to be compiler independed by building all its code only over standard
 * C functionality. In order to achive this many classes which may be redundant 
 * are build into the class library, this classes try to mantain an standard 
 * interface so they are easy to use.
 */

  
class CedarString
{
  char *p;
public:
  ///Constructor form char*.
  CedarString(const char *str);
  /// Parameterless constructor.
  CedarString();
  /// Copy constructor.
  CedarString(const CedarString &s);
  ///Destructor.
  ~CedarString() {delete [] p;}
  /// Overloaded inserter operator.
  friend ostream &operator<< (ostream &stream, CedarString &s);
  /// Overloaded extractor operator.
  friend istream &operator>> (istream &stream, CedarString &s);
  /// Assigns a CedarString Object.
  CedarString& operator= (CedarString const &s);
  /// Assigns the data contained in a char* buffer.
  CedarString& operator= (const char *s);
  /// Concatenate an CedarString object.
  CedarString& operator+ (CedarString const &s);
  /// Concatenate the data contained in a const char* buffer.
  CedarString& operator+ (const char *s);
  /// Concatenate the data contained in a int buffer.
  CedarString& operator+ (int i);
  /// Concatenate the data contained in a double buffer.
  CedarString& operator+ (double d);
  /// Concatenate the character c.
  CedarString& operator+ (char c);
  /// Returns a const pointer to the data in this object
  const char* c_str();
  /// Are two object the same?
  int operator==(CedarString &s){return !strcmp(p,s.p);}
  /// Is the data in the char* buffer s equal to this object?
  int operator==(char *s){return !strcmp(p,s);}
};

  
  
  
  
  
#endif// CedarString_h_ 
