/*******************************************************************
 * CLASS CedarParameter - Declaration
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

#ifndef CedarParameter_h_
#define CedarParameter_h_ 1

#include "CedarArray.h"
#include "CedarDataTypes.h"

class CedarString;

/**
   Encapsulates the concept of a parameter in the CEDAR database.
 */

class CedarParameter
{

  ///
  field _parameter;
  ///
  field _upper_bound;
  ///
  field _lower_bound;
  ///
  int _got_parameter;
  ///
  int _got_lower_bound;
  ///
  int _got_upper_bound;
  
  ///
  void check_bounds();

public:
  CedarParameter () :  _got_parameter(0), _got_lower_bound(0), _got_upper_bound(0) {};
  ///
  CedarParameter(field p) : _parameter(p), _got_parameter(1), _got_lower_bound(0), _got_upper_bound(0) {};
  ///
  void parse (const CedarString &st);
  ///
  CedarParameter(const CedarString &st) : _got_parameter(0), _got_lower_bound(0), _got_upper_bound(0) {this->parse (st);}
  
  /**
     @name Constraint Status analyzers
     
  */
  
  //@{
  ///
  int hasConstraint()
  {
    if (_got_lower_bound || _got_upper_bound)
      return 1;
    return 0;
  }
  ///
  int hasLowerBound()
  {
    return _got_lower_bound;
  }
  ///
  int hasUpperBound()
  {
    return _got_upper_bound;
  }
  //@}
  
  ///
  field getValue();
  ///
  field getUpperBound();
  ///
  field getLowerBound();
  ///
  void setValue(field v);
  ///
  void setUpperBound(field u);
  ///
  void setLowerBound(field l);
  ///
  unsigned int adjustData(CedarArray <field> &a);
  ///
  int operator==(const CedarParameter &p);
  ///
  int validateValue(field v)
  {
    if (_got_lower_bound && _got_upper_bound)
      {
	if ( (_lower_bound<v) && (v<_upper_bound) )
	  return 1;
	return 0;
      }
    else if (_got_lower_bound)
      {
	if (_lower_bound<v)
	  return 1;
	return 0;
      }
    else if(_got_upper_bound)
      {
	if (v<_upper_bound)
	  return 1;
	return 0;
      }
    else
      return 1;
  }

};


#endif // CedarParameter_h_
