/*******************************************************************
 * CLASS CedarString - Definition
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
#include "CedarString.h"
#include "CedarErrorHandler.h"
#include "CedarStringConversions.h"

ostream &operator<< (ostream &stream, CedarString &s)
{
  stream<<s.p;
  return stream;
  
}

istream &operator>> (istream &stream, CedarString &s)
{
  
  char t[1024];
  stream.getline(t,1024);
  delete [] s.p;
  s.p=new char [strlen(t)+1];
  strcpy (s.p,t);
  return stream;
}

CedarString::CedarString(const char *str)
{
  p=new char [strlen(str)+1];
  if (!p)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(p,str);
}

CedarString::CedarString()
{
  p=new char [1];
  if (!p)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(p,"");
}

CedarString::CedarString(const CedarString &s)
{
  p=new char[strlen(s.p)+1];
  if (!p)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(p,s.p);
}

CedarString& CedarString::operator= (CedarString const &s)
{
  if(this==&s)
    return (*this);
  delete [] p;
  p=new char [strlen(s.p)+1];
  if (!p)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(p,s.p);
  return (*this);
}

CedarString& CedarString::operator= (const char *s)
{
  delete [] p;
  p=new char [strlen(s)+1];
  if (!p)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(p,s);
  return (*this); 
}

CedarString& CedarString::operator+ (CedarString const &s)
{
  int len=strlen(p)+strlen(s.p)+1;
  char *temp= new char[len];
  if (!temp)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(temp,p);
  strcat(temp,s.p);
  delete [] p;
  p=temp;
  return (*this);
}

CedarString& CedarString::operator+ (const char *s)
{
  int len=strlen(p)+strlen(s)+1;
  char *temp= new char[len];
  if (!temp)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(temp,p);
  strcat(temp,s);
  delete [] p;
  p=temp;
  return (*this);
}

CedarString& CedarString::operator+ (int i)
{
  char buf[80];
  CedarStringConversions::ltoa(i,buf,10);
  int len=strlen(p)+strlen(buf)+1;
  char *temp= new char[len];
  if (!temp)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(temp,p);
  strcat(temp,buf);
  delete [] p;
  p=temp;
  return (*this);
}

CedarString& CedarString::operator+ (double d)
{
  char buf[80];
  CedarStringConversions::dtoa(buf,d);
  int len=strlen(p)+strlen(buf)+1;
  char *temp= new char[len];
  if (!temp)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(temp,p);
  strcat(temp,buf);
  delete [] p;
  p=temp;
  return (*this);
}

CedarString& CedarString::operator+ (char c)
{
  char buf[2];
  buf[0]=c;
  buf[1]='\0';
  int len=strlen(p)+strlen(buf)+1;
  char *temp= new char[len];
  if (!temp)
    CedarErrorHandler::errorT(CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR,"s",CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR);
  strcpy(temp,p);
  strcat(temp,buf);
  delete [] p;
  p=temp;
  return (*this);
}

const char* CedarString::c_str()
{
  return p;
}
