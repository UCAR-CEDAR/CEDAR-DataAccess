/*******************************************************************
 * CLASS CedarParameter - Definition
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

#include "CedarErrorHandler.h"
#include "CedarParameter.h"
#include "CedarString.h"


// Check the bounds to get sure that they make sense
inline void CedarParameter::check_bounds()
{
  if (_got_lower_bound && _got_upper_bound)
    {
      if ( !(_lower_bound<_upper_bound) )
	CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__INVALID_EXPRESSION,"sisisis","This CedarParameter object is out of bounds, the following expression yields false ",_lower_bound,"<",_parameter,"<",_upper_bound,"\n");
    }

    return;
}

void CedarParameter::parse (const CedarString &st)
{
  CedarString &str= (CedarString &) st; // cast away const, ugly but works...
  CedarArray <CedarString> my_strings(1,1,0);
  int len =strlen(str.c_str());
  char *data= new char[len+1];
  strcpy(data,str.c_str());
  char* front = data; // To release memory since data becomes NULL
  char* key = data; 

  if ( (data[0]=='<')  || (data[len-1]=='<') || (data[0]=='>')  || (data[len-1]=='>') )
    CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__INVALID_EXPRESSION,"sss","Invalid expression ", str.c_str(), "\n");

  unsigned short int _lower=0;

  char *p1=0, *p2=0;
  int i=0;

  while( key != NULL ) 
    { 
      p1=0; p2=0;

      i++;

      p1=strchr(data, '<');
      p2=strchr(data, '>');

      if( p1 && p2 )
	CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__INVALID_EXPRESSION,"sss","Invalid expression ", str.c_str(), " '<' can not be mixed with '>'\n");

      else if (p1 || p2)
	{
	  if (p1)
	    {
	      _lower++;
	      data=p1;
	    }
	  else
	    data=p2;

	  *data++ = '\0'; 
	}
      else
	data=NULL;
      
      my_strings[i-1]=key;
      key = data; 
    }
  delete [] front;

  if (my_strings.get_size()>3)
    CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__INVALID_EXPRESSION,"sss","Too many tokens on the expression ", str.c_str(), "\n");
  
  for(int j=0; j<i; j++)
    {
      int len=strlen(my_strings[j].c_str());
      for (int p=0;p<len;p++)
	{
	  if ((!isdigit(my_strings[j].c_str()[p])) && (my_strings[j].c_str()[p]!='-'))
	    CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__INVALID_EXPRESSION,"sss","parse error: invalid syntax on parameter-> ",my_strings[j].c_str(),"\n");
	}
    }

  if (my_strings.get_size()==1)
    {
      _got_parameter=1;
      _parameter=atoi(my_strings[0].c_str());
    }
  else if (my_strings.get_size()==2)
    {
      if (_lower==1)
	{
	  _got_parameter=1;
	  _got_upper_bound=1;
	  _parameter=atoi(my_strings[0].c_str());
	  _upper_bound=atoi(my_strings[1].c_str()); 
	}
      else
	{
	  _got_parameter=1;
	  _got_lower_bound=1;
	  _parameter=atoi(my_strings[0].c_str());
	  _lower_bound=atoi(my_strings[1].c_str()); 
	}       
    }
  else
    {
      if (_lower==2)
	{
	  _got_parameter=1;
	  _got_lower_bound=1;
	  _got_upper_bound=1;
	  _lower_bound=atoi(my_strings[0].c_str());
	  _parameter=atoi(my_strings[1].c_str());
	  _upper_bound=atoi(my_strings[2].c_str());
	}
      else
	CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__INVALID_EXPRESSION,"sss","Too many tokens on the expression ", str.c_str(), "\n");
    }
  check_bounds();
}

void CedarParameter::setValue(field v)
{
  _parameter=v;
  _got_parameter=1;
}

void CedarParameter::setUpperBound(field u)
{
  _upper_bound=u;
  _got_upper_bound=1;
  check_bounds();
}

void CedarParameter::setLowerBound(field l)
{
  _lower_bound=l;
  _got_lower_bound=1;
  check_bounds();
}

field CedarParameter::getValue()
{
    if(!_got_parameter)
	CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__OBJECT_NON_INITIALIZED,"s","This CedarParameter object has not been set\n");
    return _parameter;
}

field CedarParameter::getUpperBound()
{
    if (!_got_parameter)
	CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__OBJECT_NON_INITIALIZED,"s","This CedarParameter object has not been set\n");

    if (!_got_upper_bound)
	CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__OBJECT_NON_INITIALIZED,"s","Check to get sure there is an upper bound first\n");

    return _upper_bound;
}

field CedarParameter::getLowerBound()
{
    if (!_got_parameter)
	CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__OBJECT_NON_INITIALIZED,"s","This CedarParameter object has not been set\n");

    if (!_got_lower_bound)
	CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__OBJECT_NON_INITIALIZED,"s","Check to get sure there is an lower bound first\n");

    return _lower_bound;
}

int CedarParameter::operator==(const CedarParameter &p)
{
  if (!_got_parameter)
    CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__OBJECT_NON_INITIALIZED,"s","This CedarParameter object has not been set\n");

  if (_parameter==p._parameter)
    return 1;

  return 0;
}


unsigned int CedarParameter::adjustData(CedarArray <field> &a)
{
  if (!_got_parameter)
    CedarErrorHandler::errorT(CEDARPARAMETER__EXIT__OBJECT_NON_INITIALIZED,"s","This CedarParameter object has not been set\n");

  CedarArray <field> temp (256,256);

  register unsigned int i=0;
  register unsigned int sz=a.get_size();

  
  if (_got_lower_bound && _got_upper_bound)
    {
      for (register unsigned int j=0; j<sz; j++)
	{
	  if ( (_lower_bound<a[j]) && (a[j]<_upper_bound) )
	    {
	      temp[i]=a[j];
	      i++;
	    }
	}
      if(i>0)
	{
	  temp.set_size(i);
	  a=temp;
	  return i;
	}
    }
  else if (_got_lower_bound)
    {
      for (register unsigned int j=0; j<sz; j++)
	{
	  if (_lower_bound<a[j])
	    {
	      temp[i]=a[j];
	      i++;
	    }
	}
      if(i>0)
	{
	  temp.set_size(i);
	  a=temp;
	  return i;
	}
    }
  else if(_got_upper_bound)
    {
      for (register unsigned int j=0; j<sz; j++)
	{
	  if (a[j]<_upper_bound)
	    {
	      temp[i]=a[j];
	      i++;
	    }
	}
      if (i>0)
	{
	  temp.set_size(i);
	  a=temp;
	  return i;
	}
    }
  else
    return i;

  return 0 ;
}

