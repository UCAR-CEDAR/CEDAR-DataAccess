/*******************************************************************
 * CLASS CedarConstraintEvaluator - Definition
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

#include "CedarConfig.h"

#include <cstdlib>

#include "CedarConstraintEvaluator.h"
#include "CedarString.h"
#include "CedarErrorHandler.h"
#include "CedarString.h"
#include "CedarRecordType.h"
#include "CedarDataRecord.h"

/*
#include <fstream>

using std::ofstream ;
using std::endl ;

ofstream fstrm( "Cedar.debug" ) ;
*/

CedarConstraintEvaluator::CedarConstraintEvaluator():_records(1,1),_parameters(1,1)
{
  _got_date_constrain=0;
  _got_record_constrain=0;
  _got_parameter_constrain=0;
  _got_signature=0;
}

void CedarConstraintEvaluator::parse(const char *s)
{
  CedarString str=s;
  _got_date_constrain=0;
  _got_record_constrain=0;
  _got_parameter_constrain=0;
  _got_signature=0;
  if (!(str==""))
    {
      CedarArray <CedarString> my_strings(4,1,0);
      int len =strlen(str.c_str());
      char *data= new char[len+1];
      strcpy(data,str.c_str());
      char* front = data; // To release memory since data becomes NULL
      char* key = data; 
      int i=0;
      while( key != NULL ) 
	{ 
	  i++;
	  if ( (data = strchr(data, ';')) != NULL ) 
	    *(data++) = '\0'; 
	  my_strings[i-1]=key;
	  key = data; 
	}
      delete [] front; 
      if (i>4)
	CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s",CEDARCONSTRAINTEVALUATOR__MSG__MORE_SERVER_SIDE_FUNCTIONS_THAN_MAX_ALLOWED);
      int found_date_function=0;
      int found_record_type_function=0;
      int found_parameter_function=0;
      int found_signature_function=0;
      int  date_function, record_type_function, parameter_function, signature_function;
      char *loc;
      for(int j=0; j<i; j++)
	{
	  date_function=0; record_type_function=0; parameter_function=0; signature_function=0;
	  if (!found_date_function)
	    {
	      const char *tmpstr = "date(" ;
	      const char *mystr = my_strings[j].c_str() ;
	      loc = strstr( (char *)mystr, (char *)tmpstr ) ;
	      if( loc )
		{
		  if (((loc-my_strings[j].c_str())==0) && (my_strings[j].c_str()[(strlen(my_strings[j].c_str())-1)]==')'))
		    {
		      date_function=1;
		      found_date_function=1;
		      CedarString s="";
		      int end=strlen(my_strings[j].c_str())-1;
		      for (int p=5; p<end;p++)
			s=s+my_strings[j].c_str()[p];
		      load_dates(s);
		    }
		}
	    }
	  if (!found_record_type_function)
	    {
	      const char *tmpstr = "record_type(" ;
	      const char *mystr = my_strings[j].c_str() ;
	      loc = strstr( (char *)mystr, (char *)tmpstr ) ;
	      if( loc )
		{
		  if (((loc-my_strings[j].c_str())==0) && (my_strings[j].c_str()[(strlen(my_strings[j].c_str())-1)]==')'))
		    {
		      record_type_function=1;
		      found_record_type_function=1;
		      CedarString s="";
		      int end=strlen(my_strings[j].c_str())-1;
		      for (int p=12; p<end;p++)
			s=s+my_strings[j].c_str()[p];
		      load_records(s);
		    }
		}
	    }
	  if (!found_parameter_function)
	    {
	      const char *tmpstr = "parameters(" ;
	      const char *mystr = my_strings[j].c_str() ;
	      loc = strstr( (char *)mystr, (char *)tmpstr ) ;
	      if( loc )
		{
		  if (((loc-my_strings[j].c_str())==0) && (my_strings[j].c_str()[(strlen(my_strings[j].c_str())-1)]==')'))
		    {
		      parameter_function=1;
		      found_parameter_function=1;
		      CedarString s="";
		      int end=strlen(my_strings[j].c_str())-1;
		      for (int p=11; p<end;p++)
			s=s+my_strings[j].c_str()[p];
		      load_parameters(s);
		    }
		}
	    }
	  if (!found_signature_function)
	    {
	      const char *tmpstr = "signature(" ;
	      const char *mystr = my_strings[j].c_str() ;
	      loc = strstr( (char *)mystr, (char *)tmpstr ) ;
	      if( loc )
		{
		  if (((loc-my_strings[j].c_str())==0) && (my_strings[j].c_str()[(strlen(my_strings[j].c_str())-1)]==')'))
		    {
		      signature_function=1;
		      found_signature_function=1;
		      CedarString s="";
		      int end=strlen(my_strings[j].c_str())-1;
		      for (int p=10; p<end;p++)
			s=s+my_strings[j].c_str()[p];
		      load_signature(s);
		    }
		}
	    }
	  if (!(record_type_function || parameter_function || date_function || signature_function))
	    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"sss","parse error: invalid expresion >>",my_strings[j].c_str(),"<<\n");
	}
    }
  if (!_got_date_constrain)
    {
      _bdate.set_date(1900,101,0,0);
      _edate.set_date(2100,1231,2359,5999);
    }
}

void CedarConstraintEvaluator::load_records(CedarString &str)
{
  CedarArray <CedarString> my_strings(3,1,0);
  int len =strlen(str.c_str());
  char *data= new char[len+1];
  strcpy(data,str.c_str());
  char* front = data; // To release memory since data becomes NULL
  char* key = data; 
  int i=0;
  while( key != NULL ) 
    { 
      i++;
      if ( (data = strchr(data, ',')) != NULL ) 
	*(data++) = '\0'; 
      my_strings[i-1]=key;
      key = data; 
    }
  delete [] front; 
  for (int p=0;p<i;p++)
    {
      int len=strlen(my_strings[p].c_str());
      for (int j=0; j<len;j++)
	{
	  if ((!isdigit(my_strings[p].c_str()[j])) && (my_strings[p].c_str()[j]!='/'))
	    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error: invalid record type, only digits and '/' alowed.\n");  
	}
      load_record(p,my_strings[p]);
    }
  logged_record_type();
  _got_record_constrain=1;
}

void CedarConstraintEvaluator::load_record(int index, CedarString &str)
{
  CedarArray <CedarString> my_strings(2,1,0);
  int len =strlen(str.c_str());
  char *data= new char[len+1];
  strcpy(data,str.c_str());
  char* front = data; // To release memory since data becomes NULL
  char* key = data; 
  int i=0;
  while( key != NULL ) 
    { 
      i++;
      if ( (data = strchr(data, '/')) != NULL ) 
	*(data++) = '\0'; 
      my_strings[i-1]=key;
      key = data; 
    }
  delete [] front; 
  if (i!=2)
    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error: invalid syntax on record type.\n");
  CedarRecordType rt(atoi(my_strings[0].c_str()),atoi(my_strings[1].c_str()));
  _records[index]=rt;
}

void CedarConstraintEvaluator::load_parameters(CedarString &str)
{
  CedarArray <CedarString> my_strings(20,1,0);
  int len =strlen(str.c_str());
  char *data= new char[len+1];
  strcpy(data,str.c_str());
  char* front = data; // To release memory since data becomes NULL
  char* key = data; 
  int i=0;
  while( key != NULL ) 
    { 
      i++;
      if ( (data = strchr(data, ',')) != NULL ) 
	*(data++) = '\0'; 
      my_strings[i-1]=key;
      key = data; 
    }
  delete [] front;
  for(int j=0; j<i; j++)
    _parameters[j]=CedarParameter(my_strings[j].c_str());
  logged_parameter();
  _got_parameter_constrain=1;
}

void CedarConstraintEvaluator::load_signature(CedarString &str)
{
  signature=str;
  _got_signature=1;
}

void CedarConstraintEvaluator::load_dates(CedarString &str)
{
  CedarArray <CedarString> my_strings(8,1,0);
  int len =strlen(str.c_str());
  char *data= new char[len+1];
  strcpy(data,str.c_str());
  char* front = data; // To release memory since data becomes NULL
  char* key = data; 
  int i=0;
  while( key != NULL ) 
    { 
      i++;
      if ( (data = strchr(data, ',')) != NULL ) 
	*(data++) = '\0'; 
      my_strings[i-1]=key;
      key = data; 
    }
  delete [] front; 
  if (i!=8)
    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error:incorrect number of elements on date function.\n");
  for(int j=0; j<i; j++)
    {
      int len=strlen(my_strings[j].c_str());
      for (int p=0;p<len;p++)
	{
	  if (!isdigit(my_strings[j].c_str()[p]))
	    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error: some value for the date function is not numeric.\n");
	}
    }
  date_field begin_year=atoi(my_strings[0].c_str());
  date_field begin_date=atoi(my_strings[1].c_str());
  date_field begin_hourmin=atoi(my_strings[2].c_str());
  date_field begin_centisecond=atoi(my_strings[3].c_str());
  date_field end_year=atoi(my_strings[4].c_str());
  date_field end_date=atoi(my_strings[5].c_str());
  date_field end_hourmin=atoi(my_strings[6].c_str());
  date_field end_centisecond=atoi(my_strings[7].c_str());
  if(!_bdate.set_date(begin_year,begin_date,begin_hourmin,begin_centisecond))
    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error: invalid date value for begin date.\n");
  if (!_edate.set_date(end_year,end_date,end_hourmin,end_centisecond))
    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error: invalid date value for end date.\n");
  if(_bdate>_edate)
    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error: the begin date is bigger than the end date.\n");
  if(_bdate==_edate)
    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error: the begin date is equal to the end date.\n");
  _got_date_constrain=1;
}

int CedarConstraintEvaluator::logged_record_type()
{
  CedarArray<CedarRecordType>reg(1,1,0);
  reg[0]=_records[0];
  int max_elem=_records.get_size();
  for (int i=1; i<max_elem;i++)
    {
      for(int j=0; j<reg.get_size();j++)
	{
	  if (reg[j]==_records[i])
	    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error: repeated record type.\n");
	}
      reg[reg.get_size()]=_records[i];
    }
  return 0;
}

int CedarConstraintEvaluator::logged_parameter()
{
  CedarArray<CedarParameter>reg(1,1);
  reg[0]=_parameters[0];
  int max_elem=_parameters.get_size();
  for (int i=1; i<max_elem;i++)
    {
      for(int j=0; j<reg.get_size();j++)
	{
	  if (reg[j]==_parameters[i])
	    CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR,"s","parse error: repeated parameter type.\n");
	}
      reg[reg.get_size()]=_parameters[i];
    }
  return 0;
}

int CedarConstraintEvaluator::validate_record (const CedarLogicalRecord &dr)
{
  int is_record_OK=0;
  if (_got_record_constrain)
    {
      for(int i=0; i<_records.get_size();i++)
        {
          is_record_OK=dr.validate_record(_records[i].get_kinst(),_records[i].get_kindat(),_bdate,_edate);
          if (is_record_OK)
            return is_record_OK;
        }
    }
  else
    { 
      is_record_OK=dr.validate_record(dr.get_record_kind_instrument(),dr.get_record_kind_data(),_bdate,_edate);
    }
  return is_record_OK;
}

int CedarConstraintEvaluator::validate_record (const CedarLogicalRecord *dr)
{
  int is_record_OK=0;
  if (_got_record_constrain)
    {
      for(int i=0; i<_records.get_size();i++)
        {
          is_record_OK=dr->validate_record(_records[i].get_kinst(),_records[i].get_kindat(),_bdate,_edate);
          if (is_record_OK)
            return is_record_OK;
        }
    }
  else
    { 
      is_record_OK=dr->validate_record(dr->get_record_kind_instrument(),dr->get_record_kind_data(),_bdate,_edate);
    }
  return is_record_OK;
}
  
int CedarConstraintEvaluator::validate_parameter(short int par)
{
  if (_got_parameter_constrain)
    {
      for(int i=0; i<_parameters.get_size();i++)
	{
	  if (_parameters[i].getValue()==par)
	    {
	      return 1;
	    }
	}
      return 0;
    }
  return 1;
}

CedarParameter CedarConstraintEvaluator::get_parameter(field par)
{
    if (!_got_parameter_constrain)
    {
	CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__NOT_FOUND,"s","There are not parameter constraints, please check before using CedarConstraintEvaluator::got_parameter_constrain before calling CedarConstraintEvaluator::get_parameter\n");
    }

    bool found = false ;
    CedarParameter p ;
    for(int i=0; i < _parameters.get_size() && !found; i++ )
    {
	if (_parameters[i].getValue()==par)
	{
	    found = true ;
	    p = _parameters[i];
	}
    }
    if( !found )
    {
	CedarErrorHandler::errorT(CEDARCONSTRAINTEVALUATOR__EXIT__NOT_FOUND,"s","Parameter does not exist, please check before using CedarConstraintEvaluator::validate_parameter before calling CedarConstraintEvaluator::get_parameter\n");
    }
    return p ;
}

