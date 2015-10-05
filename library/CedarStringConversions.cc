/*******************************************************************
 * CedarStringConversions.cc Routines to perform string manipulations
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

#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cstdio>

#include "CedarConfig.h"
#include "CedarMessages.h"
#include "CedarStringConversions.h"

/*
 *  ltoa(long, char*, int) -- routine to convert a long int to the specified numeric base, from 2 to 36.
 *  Parameters: 1 - number to be converted
 *              2 - buffer in which to build the converted string
 *              3 - number base to use for conversion (2-36)
 * 
 *  Returns:  A character pointer to the converted string if
 *            successful, a NULL pointer if the number base specified
 *            is out of range.
 */

char * CedarStringConversions::ltoa(long val, char *buf,int base)                         
{
  ldiv_t r;                                 /* result of val / base  */
  if (base > 36 || base < 2)          /* no conversion if wrong base */
    {
      *buf = '\0';
      return buf;
    }
  if (val < 0)
    *buf++ = '-';
  r = ldiv (labs(val), base);
  /* output digits of val/base first */
  if (r.quot > 0)
    buf = ltoa ( r.quot, buf, base);
  
  /* output last digit */
  
  *buf++ = "0123456789abcdefghijklmnopqrstuvwxyz"[(int)r.rem];
  *buf   = '\0';
  return buf;
}

/*
 *  ltostr(long, char*, size_t, unsigned) - An improved, safer, ltoa()
 *
 *  Parameters:
 *  1.- num       =   number to convert
 *  2.- string    =   buffer for output
 *  3.- max_chars =   maximum size of buffer
 *  4.- base      =   number base for conversion.
 *
 *  Returns: if illegal base NULL else beginning of converted number.
 *
 *  Notes: if number is too large in magnitude to fit in the buffer,
 *  the MOST significant digits will be truncated.  If the number is
 *  negative, a leading '-' will be placed in the buffer even if this
 *  causes the most significant digit to be truncated.
 *  The number is right justified in the buffer and the location of the
 *  first character in the number is returned so:
 *    If you want right justification, use the original string.
 *    If you want left justification, use the returned string.
 *  If the number doesn't fill the buffer:
 *       leading characters will be filled with spaces.
 *
 */

char * CedarStringConversions::ltostr(long num, char *string, size_t max_chars, unsigned base)
{
  char remainder;
  size_t sign = 0;   /* number of digits occupied by the sign. */
  
  if (base < 2 || base > 36)
    return NULL;
  
  if (num < 0)
    {
      sign = 1;
      num = -num;
    }
  
  string[--max_chars] = '\0';
  
  for (max_chars--; max_chars > sign && num!=0; max_chars --)
    {
      remainder = (char) (num % base);
      if ( remainder < 9 )
	string[max_chars] = remainder + '0';
      else  string[max_chars] = remainder - 10 + 'A';
      num /= base;
    }
  
  if (sign)
    string[--max_chars] = '-';
  
  if ( max_chars > 0 )
    memset(string, ' ', max_chars+1);
  
  return string + max_chars;
}

/*
 *  Make an ascii hexadecimal string into an integer.
 */

unsigned int CedarStringConversions::hstr_i(char *cptr)
{
  unsigned int i, j = 0;
  
  while (cptr && *cptr && isxdigit(*cptr))
    {
      i = *cptr++ - '0';
      if (9 < i)
	i -= 7;
      j <<= 4;
      j |= (i & 0x0f);
    }
  return(j);
}

char* CedarStringConversions::version()
{
  strcpy(CedarStringConversions_version,"");
#ifdef LOGGING_WITH_CEDARDUMP
  strcat(CedarStringConversions_version,CEDARSTRINGCONVERSIONS__MSG__LOGGING_WITH_CEDARDUMP);
#endif
#ifdef CEDAR_USE_EXCEPTIONS
  strcat(CedarStringConversions_version,CEDARSTRINGCONVERSIONS__MSG__CEDAR_USE_EXCEPTIONS);
#endif
  strcat(CedarStringConversions_version,CEDARSTRINGCONVERSIONS__MSG__VERSION);
  strcat(CedarStringConversions_version, __DATE__);
  strcat(CedarStringConversions_version, " at ");
  strcat(CedarStringConversions_version, __TIME__);
  strcat(CedarStringConversions_version, "\n");
  return CedarStringConversions_version;
}


char * CedarStringConversions::dtoa(char *s, double num)
{
  sprintf(s, "%.9f", num);
  return s;
}
