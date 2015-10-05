/*******************************************************************
 * TEMPLATE CedarArray - Declaration
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

#ifndef CedarArray_h_
#define CedarArray_h_ 1

/**
   Generic template to storage data in a container "array like".
   CedarArray template is a safe container for any kind of data aligned
   in an array style and provides array services for all other classes in
   the CEDAR API. The word safes indicates that you could access elements
   beyond the maximum array size without causing SEGV (segmentation fault).
   The template handles memory from the heap via a pointer "p" to 
   generic type TYPE that is specialized at compile time.
   SIZE is an integer that indicates the size of the array. DELTA
   is an integer that indicates "how many more elements" to grow if an overflow
   is detected. Please be careful that if the data "TYPE" works with
   any kind of dynamic memory allocation it is critical that you overload 
   the = operator and the copy constructor to avoid object conflicts over areas of memory.
   Any Errors detected by the methods of this class prompts a call to CedarErrorHandler.
   The error codes for this template are in the range of [60,69]
   @see CedarErrorHandler
*/

template <class TYPE> 
class CedarArray
{
  /// Size of the array.
  int SIZE;
  /// Delta of the array to indicate how much to grow the array when an overflow is detected.
  int DELTA;
  ///
  int FAST_COPY;
  /// pointer to the allocated area where the generic data of type "TYPE" lives.
  TYPE *p;
public:
  /**
     Default Constructor. 
     Creates a CedarArray object holding elements of type TYPE. 
     Example:
     \begin{verbatim}
     CedarArray <char> some_string(15,2)
     Creates a CedarArray object to hold 15 characters and to grow by 2 elements when necessary.
     \end{verbatim} 
     If parameters are not provided, the array defaults to size=1 and delta=1.
     Example:
     \begin{verbatim}
     CedarArray <int> few_integers;
     Creates a CedarArray object to hold 1 integer and to grow by 1 elements when necessary.
     \end{verbatim}
     @param i The size for the array.
     @param h The delta for the array.
     @return An object of class CedarArray holding i elements of type TYPE and that grows h when necessary.
  */
  CedarArray(int i=1, int h=1, int fast=1);
  /**
     Copy Constructor.
     Provides explicit allocation of memory for new objects constructed based on existing objects. 
  */
  CedarArray(const CedarArray<TYPE> &y);
  /**
     Destructor.
     Deallocates the memory and destroys the object.
  */
  ~CedarArray();
  /// Flush the array by deallocating the memory where the data resides and reallocating it again.
  void flush_array();
  /**
     Set the size of the array to a new size.
     The value for new size must be major equal to one (1). 
     If the value passed to the function is not in a valid range, 
     the error handler for Cedar++ is called.
     @param new_size New size the array must grow or shrink.
     @return Data member SIZE which is equal to new_size if the method was successful.
  */
   int set_size(int new_size);
  /**
     Set the delta of the array to new_delta.
     This member function takes one parameter, int new_delta
     as the new delta for the array. The value for new delta must
     be major equal to zero (0). If the value passed to the function
     is not in a valid range, exit(int) is called since this is consider
     a fatal error.
  */
  void set_delta(int new_delta);
  /// Returns the current size of the array for const objects.
  int get_size() const {return SIZE;}
  /// Returns the current size of the array.
  int get_size() {return SIZE;};
  /// Returns the current delta of the array for const objects.
  int get_delta() const {return DELTA;}
  /// Returns the current delta of the array.
  int get_delta() {return DELTA;};
  /**
     Overloaded operator [] to detect overflows.
     By overloading the [] operator the CedarArray objects
     are capable to detect when the index used for [] is above 
     the maximum value for the current array size. If overflow is detected
     the set_size is called with parameter value current size + delta.
     If there is not an overflow, [] returns the current element reference 
     by the index in [].
  */
  TYPE& operator[](int i);
  /**
     Overloaded operator [] to detect overflows in const objects.
     By overloading the [] operator the CedarArray objects
     are capable to detect when the index used for [] is above 
     the maximum value for the current array size. 
     If overflow is detected the Cedar++ error handler is called. 
     If the index is below 0 the Cedar++ error handler is called.
     @param i Index of the requested element.
     @return A reference to requested element of type TYPE.
  */
  TYPE& operator[](int i) const;
  /**
     Overloaded assignment operator.
     When an object A is  assign the value of an object B, the =
     operator takes care of deallocating the current memory for A,
     allocating enough memory a B requires an copy the elements from 
     A to B. This is done to avoid objects sharing the same memory portion.
     For more information read your C++ documentation about objects that allocate
     memory from the heap.
  */
  CedarArray<TYPE>& operator=(const CedarArray <TYPE> &x);
  /**
     Fast copy for secure data types.
     Very fast but you really must know what you are doing in memory.
     @param add The address for the beggining of the data that you want loaded.
     @param n Number of bytes you want to move in. It must be sizeof(<Your data type>) * number of elements.
  */
  void fast_copy(void* add, unsigned n)
  {
    memcpy(p, add, n);
  }
  /**
     Expose the internal buffer of this object for fast operations. 
     Warning: You must really know what you are doing in memory to use this method.
  */
  const void* expose_buffer()
  {
    return p;
  }
};

#endif // CedarArray_h_
