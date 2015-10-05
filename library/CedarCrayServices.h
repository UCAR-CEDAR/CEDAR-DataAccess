/*******************************************************************
 * CLASS CedarCrayServices - Declaration
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

#ifndef CedarCrayServices_h_
#define CedarCrayServices_h_

#include "CedarDataTypes.h"
#include "CedarCrayBlockingStructures.h"

/**
 * Provides bit and byte operations over Cray Blocking Structures.
 * Documentation not ready.
 */

class CedarCrayServices
{
public:
  CedarCrayServices();
  ~CedarCrayServices();
  /**
   * loads a control structure (first parameter) with the data from 
   * a word structure (second parameter) acording to the rules for BCW.
   */ 
  void load_block_control(control &, word);
  /**
   * loads a control structure (first parameter) with the data from 
   * a word structure (second parameter) acording to the rules for EOR, EOF or EOD.
   */
  void load_record_control(control &, word);
  /**
   * Returns the value (0 or 1) for the bit in position with value defined by
   * the second parameter in the byte defined by first parameter. The second
   * parameter can take only values in the range [0,7]. Any other value creates
   * a fatal errors and prompts to exit the program.
   */
  int get_bit (byte, int);
  /// Returns M value for the Cray control word with data defined by the first parameter.
  int calculate_M_on_word(word);
  /// Writes the word structure defined by the first parameter into the dumper for the API.
  void show_word (word);
};

#endif // CedarCrayServices_h_
  
  
