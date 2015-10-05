/*******************************************************************
 * CLASS CedarDump - Declaration
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

#ifndef CedarDump_h_
#define CedarDump_h_ 1

#include <string>
#include <iostream>

using std::string ;
using std::ofstream ;
using std::ostream ;
using std::ios ;
using std::endl ;

#include "CedarConfig.h"
#include "CedarStringConversions.h"
#include "CedarDataTypes.h"
#include "CedarCrayBlockingStructures.h"

/**
   Main dumper for the CEDAR API.
   Although a debugger is the standard way to remove bugs, the complexities of the cray blocking as well as
   the CEDAR format for encoding data are better trace via CedarDump objects. All of the classes that conform 
   the CEDAR API (Cedar++) contain code wrapped around the pre processor macro LOGGING_WITH_CEDARDUMP. 
   When compiling with the mentioned macro this code allows the classes to write to a dump file messages 
   which defined the status of the decoding, processing, etc; in other words trace messages are directed 
   to a log file. A programmer can use this messages to better  understand the sequential manner on which 
   cbf files are being read.
   All objects of the class CedarDump share a common file handler which is initialized by the first object of
   the class being instantiated. The last object to be destroy takes care of closing and cleaning. All this
   is achieved by the use of the technique of the nifty counter (Lazy Evaluation). 
   Please notice the fact that the file handler is static. This forces its destructor to be called upon an exit
   call, therefore data sitting on the file handler buffer is committed to the file itself; by "flushing" the buffer
   before an exit call we do not loose the last trace messages which are usually the most important ones since
   they explain the status of the CEDAR API at the moment the exit call was received.
   @see LOGGING_WITH_CEDARDUMP
*/

class CedarDump 
{
  /// Singleton instance of the CedarDump class
	static CedarDump *_instance ;
  /// Flag share by all objects so they can know how to share the file handler.
        static int counter;
  /// The text file handler. This handler is shared by all objects of the class.
	static ofstream file_buffer;
  /// Flag to indicate that the file handler is open. 
	int file_is_open; 
  /// Flag to inicate that the object is not routing data to its associated stream.
	int suspended;
  /// Dumps the current system time.
	void dump_time(int) const;
public:
  /// Default constructor. 
	CedarDump(); 
  /// Destructor.
	~CedarDump();
  /// Suspend the routing of data.
	void suspend ();
  /// Resume the routing of data. 
	void resume ();
  /// Creates header based on prototype
	void puthead(const string &) const;
  /// creates tail based on prototype
	void puttail(const string &) const;
  /// Defines a data type p_ios_manipulator "pointer to function that takes ios& and returns ios&".
        typedef ios& (*p_ios_manipulator) (ios&);
  /// Defines a data type p_ostream_manipulator "pointer to function that takes ostream& and returns ostream&".
	typedef ostream& (*p_ostream_manipulator) (ostream&);
  /**
     @name Overloaded inserterers
     This inserterers make easy to send data to the text file.
  */
  //@{
    /// Overloaded inserter for string
	     CedarDump& operator << (string &);
    /// Overloaded inserter for int.
	     CedarDump& operator << (int);
    /// Overloaded inserter for char.
	     CedarDump& operator << (char);
    /// Overloaded inserter for long.
	     CedarDump& operator << (long);
    /// Overloaded inserter for double.
	     CedarDump& operator << (double);
    /// Overloaded inserter for CEDAR data type bit.
	     CedarDump& operator << (bit);
    /// Overloaded inserter for CEDAR data type byte.
	     CedarDump& operator << (byte);
    /// Overloaded inserter for CEDAR data type field.
	     CedarDump& operator << (field);
    /// Overloaded inserter for CEDAR data type date_field.
	     CedarDump& operator << (date_field);
    /** 
	Overloaded inserter that can take the address of endl, flush and ends functions.
	This inserter is based on p_ostream_manipulator, therefore the C++ standard functions for I/O 
	endl, flush, and ends can be applied to objects of the class CedarDump.
    */
	     CedarDump& operator<<(p_ostream_manipulator); 
    /** 
	Overloaded inserter that can take the address oct, dec and hex functions.
	This inserter is based on p_ios_manipulator, therefore the C++ standard functions oct, dec and hex
	can be applied to objects of the class CedarDump.
    */ 
             CedarDump& operator<<(p_ios_manipulator); 
    /// Overloaded inserter for string for const objects.
	     const CedarDump& operator << (const string &) const;
    /// Overloaded inserter for int for const objects.
             const CedarDump& operator << (int) const;
    /// Overloaded inserter for char for const objects.
             const CedarDump& operator << (char) const;
    /// Overloaded inserter for long for const objects.
             const CedarDump& operator << (long) const;
    /// Overloaded inserter for double for const objects.
             const CedarDump& operator << (double) const;
    /// Overloaded inserter for CEDAR data type bit for const objects.
	     const CedarDump& operator << (bit) const;
    /// Overloaded inserter for CEDAR data type byte for const objects.
	      const CedarDump& operator << (byte) const;
    /// Overloaded inserter for CEDAR data type field for const objects.
	      const CedarDump& operator << (field) const;
    /// Overloaded inserter for CEDAR data type date_field for const objects.
	      const CedarDump& operator << (date_field) const;
    /** 
	Overloaded inserter for const objects that can take the address of endl, flush and ends functions.
	This inserter is based on p_ostream_manipulator, therefore the C++ standard functions for I/O 
	endl, flush, and ends can be applied to objects of the class CedarDump.
    */
	      const CedarDump& operator<<(p_ostream_manipulator) const; 
    /** 
	Overloaded inserter for const objects that can take the address oct, dec and hex functions.
	This inserter is based on p_ios_manipulator, therefore the C++ standard functions oct, dec and hex
	can be applied to objects of the class CedarDump.
    */ 
	      const CedarDump& operator<<(p_ios_manipulator) const; 
  //@}

    static CedarDump &Dumper() ;
};

#endif // CedarDump_h_
