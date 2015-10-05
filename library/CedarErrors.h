/*******************************************************************
 * CEDAR API - Exit values.
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

#ifndef CedarErrors_h_
#define CedarErrors_h_ 1

/*
 * Numeric values used by exit(int).
 *
 * The Cedar API calls exit(int) when what is consider a fatal error is detected.
 *
 * Syntax for CEDAR API Exit values:
 * "CLASSNAME" + EXIT + "EXIT NAME"
 *
 * where:
 *
 * "CLASSNAME"         identifies the class that is using the message.
 * "EXIT NAME"         Any name you may wish for your exit value.
 *
 * "CLASSNAME" and  the EXIT word and "MESSAGE NAME" are linked by duble under score ( __ ).
 * "EXIT NAME" words are linked with single under score ( _ ).
 *
 */

// ERRORS IN CLASS CedarDump.

#define CEDARDUMP__EXIT__FATAL_OPENING_FILE_BUFFER			50

// ERRORS IN TEMPLATE CedarArray.

#define CEDARARRAY__EXIT__INVALID_SIZE_OR_DELTA_PARAMETERS		60
#define CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_FORMAL_ARRAY		61
#define CEDARARRAY__EXIT__ARRAY_SIZE_SMALLER_THAN_ONE			62
#define CEDARARRAY__EXIT__COULD_NOT_GET_MEMORY_TEMP_ARRAY		63
#define CEDARARRAY__EXIT__DELTA_CAN_NOT_BE_NEGATIVE			64
#define CEDARARRAY__EXIT__CAN_NOT_ACCESS_INDEX_BELLOW_ZERO_IN_ARRAY	65
#define CEDARARRAY__EXIT__OVERFLOW_WHEN_DELTA_IS_EQUAL_TO_ZERO		66
#define CEDARARRAY__EXIT__OUT_OF_BOUNDARIES_ON_CONST_OBJECT             67

// ERRORS IN class CedarBlock.

#define CEDARBLOCK__EXIT__DATE_FIELD_NEGATIVE				70
#define CEDARBLOCK__EXIT__INVALID_DATE					71
#define CEDARBLOCK__EXIT__NEGATIVE_PROLOGUE_VALUE                       72

// ERRORS IN class CedarCrayServices.

#define CEDARCRAYSERVICES__EXIT__ACCESING_WRONG_BIT			80

// ERRORS IN class CedarFile.

#define CEDARFILE__EXIT__FILENAME_NULL					90
#define CEDARFILE__EXIT__FILE_NAME_TOO_LONG				91
#define CEDARFILE__EXIT__TYPE_OF_CONTROL				92
#define CEDARFILE__EXIT__GETTING_NEXT					93
#define CEDARFILE__EXIT__INVALID_FORWARD_INDEX                          94
#define CEDARFILE__EXIT__BAD_CHECK_SUM                                  95
#define CEDARFILE__EXIT__MUST_BE_END_OF_DATASET                         96
#define CEDARFILE__EXIT__NOT_SUPPORTED_CACHE                            97
#define CEDARFILE__EXIT__CAN_NOT_GET_FILE_STAT                          98
#define CEDARFILE__EXIT__CAN_NOT_CREATE_READ_AHEAD_THREAD               99
#define CEDARFILE__EXIT__UNKNOWN_FORMAT                                100
#define CEDARFILE__EXIT__FILE_NOT_OPEN                                 101
#define CEDARFILE__EXIT__SIGWORDS_LESS_THAN_0                          102
#define CEDARFILE__EXIT__FIRSTWORD_FIRSTLR_LT_0                        103
#define CEDARFILE__EXIT__FIRSTWORD_LASTLR_LT_0                         104
#define CEDARFILE__EXIT__FIRSTWORD_FIRSTLR_SET_0                       105
#define CEDARFILE__EXIT__LENGTH_FIRSTLR_LT_0                           106

// ERRORS IN class CedarConstraintEvaluator

#define CEDARCONSTRAINTEVALUATOR__EXIT__PARSE_ERROR                     110
#define CEDARCONSTRAINTEVALUATOR__EXIT__NOT_FOUND                       111

// ERRORS IN class CedarParameters

#define CEDARPARAMETER__EXIT__INVALID_EXPRESSION                        120
#define CEDARPARAMETER__EXIT__OBJECT_NON_INITIALIZED                    121

// ERRORS IN class CedarString

#define CEDARSTRING__EXIT__MEMORY_ALLOCATION_ERROR                      130


 
#endif // CedarErrors_h_
