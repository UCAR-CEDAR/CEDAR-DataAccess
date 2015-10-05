/*******************************************************************
 * CLASS CedarConstraintEvaluator - Declaration
 * CLASS CedarStringConversions - Declaration
 * Wrapper class for routines to perform string manipulations
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

#ifndef CedarStringConversions_h_
#define CedarStringConversions_h_ 1

#include <cstddef>

/**
 * Miscellaneous string manipulations required by the CEDAR API.
 * All the member functions are declared static so you do not need
 * to instantiate an object to call these functions. Use a syntax like:
 * "CedarStringConversions::ltoa(234,buffer,16);" to access the routines.
 * Documentation not ready.
 */

class CedarStringConversions
{
  char CedarStringConversions_version [800];
  char* version();
  friend class CedarVersion;
public:
  /// Routine to convert a long int to the specified numeric base, from 2 to 36.
  static char* ltoa(long, char*, int);
  /// An improved, safer, ltoa().
  static char* ltostr(long, char*, size_t, unsigned);
  /// Make an ascii hexadecimal string into an integer.
  static unsigned int hstr_i(char *);
  /// Converts a double to a string as char*.
  static char * dtoa(char *s, double num);
};

#endif // CedarStringConversions_h_


/*
 * This class was created to wrap C functions in a more object oriented environment.
 * 1.- If we would have leave this functions as they were in C, you may have plenty problems 
 * of unresolved symbols because the unit of compilation may be created with a C compiler
 * and the rest of the CEDAR API in C++, then the linker does not know what to do.
 * 2.- By using class definitions we can created this module with the same style of the 
 * whole API, making the interface more homogeneous. In other words, by creating the 
 * class CedarStringConversions the C functions prototypes are in this header file (in the class
 * declaration) that besides includes CedarConfig.h therefore  the goal of controlling
 * system header files and global macro definition in one master header file is achieved.
 * 3.- Wrapping C functions in a class holds better the spirit of the CEDAR API
 * 4.- By declaring the functions static you can access the functions without instantiating
 * and object. do so like:
 * ...
 * CedarStringConversions::ltoa(...)
 * ... 
 */

/************************************************* Credits ***********************************************
 *
 *  ltoa(long, char*, int) -- routine to convert a long int to the specified numeric base, from 2 to 36.
 *  Written by Thad Smith III, Boulder, CO. USA  9/06/91 and contributed to the Public Domain.
 *
 *  ltostr(long, char*, size_t, unsigned) -- An improved, safer, ltoa()
 *  public domain by Jerry Coffin
 * 
 *  unsigned int hstr_i(char *cptr) -- Make an ascii hexadecimal string into an integer.
 *  Originally published as part of the MicroFirm Function Library
 *  Copyright 1986, S.E. Margison
 *  Copyright 1989, Robert B.Stout
 *  The user is granted a free limited license to use this source file
 *  to create royalty-free programs, subject to the terms of the
 *  license restrictions specified in the LICENSE.MFL file.
 *
 *********************************************************************************************************/

/************************************************* LICENSE.MFL ***********************************************
 * Portions of SNIPPETS code are Copyright 1987-1996 by Robert B. Stout dba
 * MicroFirm. The user is granted a free license to use these source files in
 * any way except for commercial publication other than as part of your own
 * program. This means you are explicitly granted the right to:
 * 
 * 1.  Use these files to create applications for any use, private or commercial,
 *     without any license fee.
 * 
 * 2.  Copy or otherwise publish copies of the source files so long as the
 *     original copyright notice is not removed and that such publication is 
 *     free of any charges other than the costs of duplication and distribution.
 * 
 * 3.  Distribute modified versions of the source files so long as the original
 *     copyright notice is not removed, and that the modified nature is clearly
 *     noted in the source file, and that such distribution is free of any
 *     charges other than the costs of duplication and distribution.
 * 
 * 4.  Distribute object files and/or libraries compiled from the supplied
 *     source files, provided that such publication is free of any charges other 
 *     than the costs of duplication and distribution.
 * 
 * Rights reserved to the copyright holder include:
 * 
 * 1.  The right to publish these works commercially including, but not limited
 *     to, books, magazines, and commercial software libraries.
 * 
 * 2.  The commercial rights, as cited above, to all derivative source and/or
 *     object modules. Note that this explicitly grants to the user all rights,
 *     commercial or otherwise, to any and all executable programs created using
 *     MicroFirm copyrighted source or object files contained in SNIPPETS.
 * 
 * Users are specifically prohibited from:
 * 
 * 1.  Removing the copyright notice and claiming the source files or any
 *     derivative works as their own.
 * 
 * 2.  Publishing the source files, the compiled object files, or libraries of
 *     the compiled object files commercially.
 * 
 * In other words, you are free to use these files to make programs, not to make
 * money! The programs you make with them, you may sell or give away as you
 * like, but you many not sell either the source files or object files, alone
 * or in a library, even if you've modified the original source, without a
 * license from the copyright holder.
 * 
 *********************************************************************************************************/
