/*******************************************************************
 * CedarCrayBlockingStructures - Basic Data Types
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

#ifndef CedarCrayBlockingStructures_h_
#define CedarCrayBlockingStructures_h_ 1

/**
 * Definition of the data type bit
 * bit is self explanatory.
 */

typedef unsigned  bit;

/**
 * Definition of the data type word_TAG.
 * word_TAG is a bit field structure containing 64 bit. 
 * It has been designed to storage in real bits a Cray control word of 8 bytes. 
 * (check bit fields in the C language for more information about bit fields) 
 * You should check that your compiler storages a word as 8 bytes for the CEDAR API to work correctly.
 */

struct word_TAG
{
  bit b0  : 1;  bit b1  : 1;  bit b2  : 1;  bit b3  : 1;  bit b4  : 1;  bit b5  : 1;  bit b6  : 1;  bit b7  : 1;
  bit b8  : 1;  bit b9  : 1;  bit b10 : 1;  bit b11 : 1;  bit b12 : 1;  bit b13 : 1;  bit b14 : 1;  bit b15 : 1;
  bit b16 : 1;  bit b17 : 1;  bit b18 : 1;  bit b19 : 1;  bit b20 : 1;  bit b21 : 1;  bit b22 : 1;  bit b23 : 1;
  bit b24 : 1;  bit b25 : 1;  bit b26 : 1;  bit b27 : 1;  bit b28 : 1;  bit b29 : 1;  bit b30 : 1;  bit b31 : 1;
  bit b32 : 1;  bit b33 : 1;  bit b34 : 1;  bit b35 : 1;  bit b36 : 1;  bit b37 : 1;  bit b38 : 1;  bit b39 : 1;
  bit b40 : 1;  bit b41 : 1;  bit b42 : 1;  bit b43 : 1;  bit b44 : 1;  bit b45 : 1;  bit b46 : 1;  bit b47 : 1;
  bit b48 : 1;  bit b49 : 1;  bit b50 : 1;  bit b51 : 1;  bit b52 : 1;  bit b53 : 1;  bit b54 : 1;  bit b55 : 1;
  bit b56 : 1;  bit b57 : 1;  bit b58 : 1;  bit b59 : 1;  bit b60 : 1;  bit b61 : 1;  bit b62 : 1;  bit b63 : 1;
};

/**
 * Use word as a data type instead of struct word_TAG. 
 * It is defined as: typedef struct word_TAG word.
 */

typedef struct word_TAG word;

/** 
 * Definition of the data type block_control_word_TAG. 
 * block_control_word_TAG and record_control_word_TAG represent the specialization of
 * the word_TAG data type. block_control_word is_TAG the implementation of BCW.
 * record_control_word_TAG is the implementation for either EOR, EOF or EOD.
 * Just as defined in the COS reference manual some bit fields are unused.
 * For example in block_control_word_TAG bits 4-10 are undefined so they can not be 
 * accessed from outside the structure. In both cases the FWI (forward index) member
 * is defined as the last 9 bits for the words. For a detailed information about the 
 * members of block_control_word_TAG and record_control_word_TAG you should refer to
 * the "COS reference manual."
 */

struct  block_control_word_TAG
{
  bit M : 4;
  bit : 7;
  bit BDF : 1;
  bit : 19;
  bit BN : 24 ;
  bit FWI : 9;
};

/**
 * Use block_control_word as a data type instead of struct block_control_word_TAG. 
 * It is defined as: typedef struct block_control_word_TAG block_control_word .
 *
 */

typedef struct block_control_word_TAG block_control_word;

/** 
 * Definition of the data type record_control_word_TAG. 
 * block_control_word_TAG and record_control_word_TAG represent the specialization of
 * the word_TAG data type. block_control_word is_TAG the implementation of BCW.
 * record_control_word_TAG is the implementation for either EOR, EOF or EOD.
 * Just as defined in the COS reference manual some bit fields are unused.
 * For example in block_control_word_TAG bits 4-10 are undefined so they can not be 
 * accessed from outside the structure. In both cases the FWI (forward index) member
 * is defined as the last 9 bits for the words. For a detailed information about the 
 * members of block_control_word_TAG and record_control_word_TAG you should refer to
 * the "COS reference manual."
 */

struct record_control_word_TAG
{
  bit M : 4;
  bit UBC : 6;
  bit TRAN : 1;
  bit BDF : 1;
  bit SRS : 1;
  bit : 7;
  bit PFI : 20;
  bit PRI : 15;
  bit FWI : 9;
};

/**
 * Use record_control_word as a data type instead of struct record_control_word_TAG. 
 * It is defined as: typedef struct record_control_word_TAG record_control_word.
 *
 */

typedef struct record_control_word_TAG record_control_word;

/** 
 * Definition of the data type type_of_control_word_TAG.
 * The enumeration type_of_control_word_TAG enforces that a control data type
 * can only have BCW, EOR, EOF or EOD as the values for its member type_of_control. 
 */

enum type_of_control_word_TAG
{
  cray_BCW=0, cray_EOR=8, cray_EOF=14, cray_EOD=15
};

/**
 * Use type_of_control_word as a data type instead of enum type_of_control_word_TAG.
 * It is defined as: typedef enum type_of_control_word_TAG  type_of_control_word.
 *
 */

typedef enum type_of_control_word_TAG  type_of_control_word;

/** 
 * Definition of the data type control_TAG.
 * control_TAG is a high level structure and it is used by CedarFile class as 
 * a way to wrap the concept of a control no matter what kind it is.
 * 1.- type_of_control: A control can be BCW, EOR, EOF or EOD and that information is storage 
 *                      in this member. 
 * 2.- block_control:   If type of control is BCW  the information about the control is storage 
 *                      in this member.
 * 3.- record_control:  If type of control is  either EOR, EOF or EOD the information about the 
 *                      control is storage in this member.
 * 4.- forward index:   contains the information for how many words forward is the next control.
 *                      When moving sequentially in a byte mode you should multiply the forward 
 *                      index by 8 to get the byte count of how many byte forward is the next control.
 *
 * The members block_control and record_control MUTUALLY EXCLUSIVE that is:
 * A) if type_of_control is BCW the information is storage in the member block_control
 *    and record_control SHOULD BE IGNORED
 * B) if type_of_control is either EOR, EOF or EOD the information is storage in the 
 *    member record_control and block_control SHOULD BE IGNORED. 
 */

struct control_TAG
{
  type_of_control_word  type_of_control;
  block_control_word    block_control;
  record_control_word   record_control;
  int forward;
};

/**
 * Use control as a data type instead of struct control_TAG. 
 * It is defined as: typedef struct control_TAG control .
 *
 */

typedef struct control_TAG control;


#endif // CedarCrayBlockingStructures_h_



