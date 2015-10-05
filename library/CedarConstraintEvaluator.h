/*******************************************************************
 * CLASS CedarConstraintEvaluator - Declaration
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

#ifndef CedarConstraintEvaluator_h_
#define CedarConstraintEvaluator_h_ 1

#include "CedarArray.h"
#include "CedarDate.h"
#include "CedarString.h"
#include "CedarLogicalRecord.h"
#include "CedarParameter.h"

// Forward declaration
class CedarRecordType;

/**
   Constraint Evaluations for Cedar.
*/

class CedarConstraintEvaluator
{
  ///
  CedarString signature;
  ///
  CedarDate _bdate;
  ///
  CedarDate _edate;
  ///
  CedarArray<CedarRecordType> _records;
  ///
  CedarArray <CedarParameter> _parameters;
  ///
  int _got_date_constrain;
  ///
  int _got_record_constrain;
  ///
  int _got_parameter_constrain;
  ///
  int _got_signature;
  ///
  void load_dates(CedarString &);
  ///
  void load_records(CedarString &);
  ///
  void load_record(int index, CedarString &);
  ///
  void load_parameters(CedarString &);
  ///
  void load_signature(CedarString &);
  ///
  int logged_record_type();
  ///
  int logged_parameter();
public:
  ///
  CedarConstraintEvaluator();
  ///
  void parse (const char *s);
  ///
  CedarDate get_begin_date(){return _bdate;}
  ///
  CedarDate get_end_date (){return _edate;}
  ///
  CedarArray<CedarRecordType> get_record_types(){return _records;}
  ///
  CedarArray<CedarParameter> get_parameters(){return _parameters;}
  ///
  int got_date_constrain(){return _got_date_constrain;}
  ///
  int got_record_constrain(){return _got_record_constrain;}
  ///
  int got_parameter_constraint(){return _got_parameter_constrain;}
  ///
  int got_signature(){return _got_signature;}
  ///
  int validate_record (const CedarLogicalRecord &dr);
  ///
  int validate_record (const CedarLogicalRecord *dr);
  ///
  int validate_parameter(field par);
  ///
  CedarParameter get_parameter(field par);
  ///
  const char* get_signature()
  {
    if  (_got_signature) 
      return signature.c_str();
    else
      return 0;
  }
};

#endif // CedarConstraintEvaluator_h_
