/*******************************************************************
 * TEMPLATE Class CedarArray - Definition
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

#include <cstring>

#include "CedarConfig.h"
#include "CedarArray.h"
#include "CedarErrorHandler.h"
#ifdef LOGGING_WITH_CEDARDUMP
#include "CedarDump.h"
#endif

template <class TYPE> 
CedarArray<TYPE>::CedarArray(int i, int h, int fast)
{
  FAST_COPY=fast;
  p=NULL;
  if (i<1 || h<0) 
    CedarErrorHandler::errorT(CEDARARRAY__EXIT__INVALID_SIZE_OR_DELTA_PARAMETERS,"s",CEDARARRAY__FATAL__WRONG_SIZE_OR_DELTA);
  SIZE=i;
  DELTA=h;
  try
    {
      p=new TYPE [SIZE];
    }
  catch(...)
    {
      CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_FORMAL_ARRAY,"s",CEDARARRAY__FATAL__EXCEPTION_REPORTED_OPERATOR_NEW);
    }
  if (!p) 
    CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_FORMAL_ARRAY,"s",CEDARARRAY__FATAL__ALLOCATION_ERROR_FOR_BUFFER_P);
#ifdef LOGGING_WITH_CEDARDUMP
  // If we are dumping into a trace log, this portion of code will take care of that...
  CedarDump::Dumper().puthead(CEDARARRAY__PROTOTYPE__1); 
  CedarDump::Dumper()<<CEDARARRAY__MSG__ARRAY_CONSTRUCTED; 
  CedarDump::Dumper()<<CEDARARRAY__MSG__NEW_OBJECT_SIZE<<SIZE<<ENDL; 
  CedarDump::Dumper()<<CEDARARRAY__MSG__NEW_OBJECT_DELTA<<DELTA<<ENDL; 
  CedarDump::Dumper()<<CEDARARRAY__MSG__AMOUNT_OF_MEMORY_IN_USE<<SIZE<<"*"<<(long)sizeof(TYPE)<<"="<<(long)(SIZE*sizeof(TYPE))<<ENDL;
  CedarDump::Dumper().puttail(CEDARARRAY__PROTOTYPE__1);
#endif
}

// Copy Constructor follows...

template <class TYPE> 
CedarArray<TYPE>::CedarArray(const CedarArray <TYPE> &y)
{  
  p=NULL;
  // This new object must get its own memory in the heap base on the area of constant object "y"
  try
    {
      p=new TYPE[y.SIZE];
    }
  catch(...)
    {
      CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_FORMAL_ARRAY,"s",CEDARARRAY__FATAL__EXCEPTION_REPORTED_OPERATOR_NEW);
    }
  if (!p)
    {
      CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_FORMAL_ARRAY,"s",CEDARARRAY__FATAL__ALLOCATION_ERROR_FOR_BUFFER_P);
    }
  // copy elements from buffer of constant object y to the buffer of this new object
  // This involves using the = operator associated with data type TYPE
  if (FAST_COPY)
    memcpy(p,y.p,y.SIZE*sizeof(TYPE));
  else
    for (int j=0; j<y.SIZE; j++) p[j]=y.p[j];
  SIZE=y.SIZE;
  DELTA=y.DELTA;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARARRAY__PROTOTYPE__3); 
  CedarDump::Dumper()<<CEDARARRAY__MSG__DEBUGGING_INHERITED; 
  CedarDump::Dumper().puttail(CEDARARRAY__PROTOTYPE__3);
#endif
}

template <class TYPE> 
CedarArray<TYPE>::~CedarArray()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead (CEDARARRAY__PROTOTYPE__2);
  CedarDump::Dumper()<<CEDARARRAY__MSG__DESTRUCTING_ARRAY;
  CedarDump::Dumper().puttail (CEDARARRAY__PROTOTYPE__2);
#endif
  // deallocating the memory from the heap...
  if(p)
    {
      delete [] p;
      p=0;
    }
}

/*
 * flush_array() will try to release the memory and allocate it again. 
 * After that notice that the array's elements are not initialized... 
 */

template <class TYPE> 
void CedarArray<TYPE>::flush_array()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARARRAY__PROTOTYPE__6);
  CedarDump::Dumper()<<CEDARARRAY__MSG__FLUSHING_ARRAY;
#endif
  delete [] p;
  try
    {
      p= new TYPE [SIZE];
    }
  catch(...)
    {
      CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_FORMAL_ARRAY,"s",CEDARARRAY__FATAL__EXCEPTION_REPORTED_OPERATOR_NEW);
    }  
  if (!p)
    {
      CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_FORMAL_ARRAY,"s",CEDARARRAY__FATAL__ALLOCATION_ERROR_FOR_BUFFER_P);
    }
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper()<<CEDARARRAY__MSG__ARRAY_FLUSHED;
  CedarDump::Dumper().puttail(CEDARARRAY__PROTOTYPE__6);
#endif
}

template <class TYPE> 
int CedarArray<TYPE>::set_size(int new_size)
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARARRAY__PROTOTYPE__9);
  CedarDump::Dumper()<<CEDARARRAY__MSG__ARRAY_SIZE<<SIZE<<" ,"<<new_size<<ENDL;
  CedarDump::Dumper()<<CEDARARRAY__MSG__AMOUNT_OF_MEMORY_IN_USE<<(long)(SIZE*sizeof(TYPE))<<ENDL;
#endif
  if(new_size==SIZE)
    return SIZE;
  if(new_size<1)
      CedarErrorHandler::errorT(CEDARARRAY__EXIT__ARRAY_SIZE_SMALLER_THAN_ONE,"s",CEDARARRAY__FATAL__CAN_NOT_ACCESS_NEGATIVE_INDEX);
  TYPE *temp = 0 ;
  try
    {
      temp = new TYPE[new_size];
    }
  catch(...)
    {
      CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_TEMP_ARRAY,"s",CEDARARRAY__FATAL__EXCEPTION_REPORTED_OPERATOR_NEW);
    }
  if (!temp) 
      CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_TEMP_ARRAY,"s",CEDARARRAY__FATAL__ALLOCATION_ERROR_FOR_BUFFER_TEMP);
  /*
   * To calculate h (how many elements to copy) we say; 
   * if new_size is smaller than SIZE we can copy only new_size elements
   * and elements above new_size are lost, else we can copy all SIZE elements
   * if by any chance new_size==SIZE then all SIZE elements are copied.
   */
  int h=new_size<SIZE ? new_size : SIZE ;
  // Copying elements...
  if(FAST_COPY)
    memcpy(temp,p,h*sizeof(TYPE));
  else
    for (int j=0; j<h; j++) temp[j]=p[j];
  delete [] p;
  p=temp;
  SIZE=new_size;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper()<<CEDARARRAY__MSG__SET_SIZE_SUCCEED;
  CedarDump::Dumper()<<CEDARARRAY__MSG__AMOUNT_OF_MEMORY_IN_USE<<(long)(SIZE*sizeof(TYPE))<<ENDL;
  CedarDump::Dumper().puttail(CEDARARRAY__PROTOTYPE__9);
#endif
  return SIZE;
}

template <class TYPE> 
void CedarArray<TYPE>::set_delta(int new_delta)
{
    if (new_delta < 0)
    {
	CedarErrorHandler::errorT(CEDARARRAY__EXIT__DELTA_CAN_NOT_BE_NEGATIVE,"s",CEDARARRAY__FATAL__DELTA_CAN_NOT_BE_SMALLER_THAN_ZERO);
    }
	
    DELTA = new_delta ;
}

template <class TYPE> 
TYPE &CedarArray <TYPE>::operator[](int i)
{
    // if the size is greater than zero and less than the current size of
    // the array then return that element
    if ( (0<=i) && (i<SIZE) )
    {
	return p[i];
    }

    // if the index is less than zero then throw an error
    if (i<0)
    {
	#ifdef LOGGING_WITH_CEDARDUMP
	CedarDump::Dumper().puthead(CEDARARRAY__PROTOTYPE__7); 
	CedarDump::Dumper()<<CEDARARRAY__MSG__OUT_OF_BOUNDARIES<<i<< " ,"<<SIZE<<ENDL; 
	CedarDump::Dumper().puttail(CEDARARRAY__PROTOTYPE__7);
	#endif 

	CedarErrorHandler::errorT(CEDARARRAY__EXIT__CAN_NOT_ACCESS_INDEX_BELLOW_ZERO_IN_ARRAY,"s",CEDARARRAY__FATAL__CAN_NOT_ACCESS_NEGATIVE_INDEX);
    }

    // the index is greater than or equal to the current SIZE, either grow
    // the array, if it is allowed, or throw an error
    #ifdef LOGGING_WITH_CEDARDUMP
    CedarDump::Dumper().puthead(CEDARARRAY__PROTOTYPE__7); 
    CedarDump::Dumper()<<CEDARARRAY__MSG__OUT_OF_BOUNDARIES<<i<< " ,"<<SIZE<<ENDL; 
    #endif

    if (DELTA<1)
    {
	/* we can not grow if delta does not let us
	* that prompts an error, let the error handler take care of it.
	*/
	CedarErrorHandler::errorT(CEDARARRAY__EXIT__OVERFLOW_WHEN_DELTA_IS_EQUAL_TO_ZERO,"s",CEDARARRAY__FATAL__CAN_NOT_GROW_ARRAY_WITH_DELTA_ZERO);
    }

    #ifdef LOGGING_WITH_CEDARDUMP
    CedarDump::Dumper()<<CEDARARRAY__MSG__CALLING_SET_SIZE;
    CedarDump::Dumper().puttail(CEDARARRAY__PROTOTYPE__7);
    #endif

    set_size(i+DELTA);
    return p[i];
}

template <class TYPE> 
TYPE& CedarArray <TYPE>::operator[](int i) const
{
    if ((i<0)||(i>SIZE-1))
    {
	CedarErrorHandler::errorT(CEDARARRAY__EXIT__OUT_OF_BOUNDARIES_ON_CONST_OBJECT,"sisis",CEDARARRAY__MSG__OUT_OF_BOUNDARIES,i," ,",SIZE,ENDL);
    }
    return p[i];
}

template <class TYPE> 
CedarArray<TYPE> &CedarArray <TYPE>::operator=(CedarArray<TYPE> const &x)
{
#ifdef LOGGING_WITH_CEDARDUMP
    CedarDump::Dumper().puthead(CEDARARRAY__PROTOTYPE__8);
    CedarDump::Dumper()<<CEDARARRAY__MSG__CALLING_OVERLOADED_EQUAL; 
#endif
    if (this == &x)
    {
#ifdef  LOGGING_WITH_CEDARDUMP
	CedarDump::Dumper()<<CEDARARRAY__MSG__DEBUGGING_INHERITED;
	CedarDump::Dumper().puttail(CEDARARRAY__PROTOTYPE__8);
#endif 
	return *this;
    }
	  
    // We must release the memory we own and re allocate based on the size of the constant object x
    delete[] p;

    try
    {
	p=new TYPE [x.SIZE];
    }
    catch(...)
    {
	CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_FORMAL_ARRAY,"s",CEDARARRAY__FATAL__EXCEPTION_REPORTED_OPERATOR_NEW);
    }

    if (!p)
    {
	CedarErrorHandler::errorT(CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_FORMAL_ARRAY,"s",CEDARARRAY__FATAL__ALLOCATION_ERROR_FOR_BUFFER_P);
    }

    // Copy of the elements of constant object x into this object...
    if (FAST_COPY)
	memcpy(p,x.p,x.SIZE*sizeof(TYPE));
    else
	for (int h=0; h<x.SIZE; h++)
	{
	    p[h]=x.p[h];
	}
    SIZE=x.SIZE;
    DELTA=x.DELTA;

#ifdef  LOGGING_WITH_CEDARDUMP
    CedarDump::Dumper()<<CEDARARRAY__MSG__DEBUGGING_INHERITED;
    CedarDump::Dumper().puttail(CEDARARRAY__PROTOTYPE__8);
#endif

    return *this;
}

