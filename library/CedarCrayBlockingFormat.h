/*******************************************************************
 * CLASS CedarCrayBlockingFormat - Declaration
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

#ifndef CedarCrayBlockingFormat_h_
#define CedarCrayBlockingFormat_h_ 1

#include <fstream>

using std::ifstream ;

#include "CedarCrayServices.h"
#include "CedarBlock.h"
#include "CedarGroup.h"
#include "CedarPhysicalFile.h"

#ifdef CEDAR_USE_MULTITHREAD
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <queue>

class CedarDump ;

struct read_ahead_buffer
{
  byte *buf;
  int used;
};

struct read_ahead_thread_parameters
{
  int number_of_read_ahead_buffers;
  struct read_ahead_buffer * buffers;
  ifstream *pos;
  pthread_mutex_t *mutex;
  int running;
  int os_status;
  queue<int> q;
  int number_of_wait;
  CedarDump *pdumper;
};

typedef struct read_ahead_thread_parameters thread_parameters;

void* read_ahead(thread_parameters *pars);

#endif // CEDAR_USE_MULTITHREAD


/// SIZE_OF_COS_BLOCK optimal size in bytes for file reading.
#define SIZE_OF_COS_BLOCK 4096


/**
   Encapsulates data and behavior for CBF files.
   Documentation not ready.
*/

class CedarCrayBlockingFormat : public CedarPhysicalFile
{
  ///
  CedarBlock cdBlock;
  ///
  const CedarLogicalRecord* plogrec;

  /// Flag set to true when the object is constructed with CEDAR_DO_BLOCK_CHECK_SUM.
  int check_sum_on_blocks;
  /// Name for this object base on the CBF file being used.
  char name [MAXFILENAME];
  /// Internal control flags.
  int  connected, has_name, block_counter, block_number, end_of_dataset, can_get_more;
  /// word variable to handle word operations.
  word my_word;
  /// control variable to handle control operations.
  control my_control;
  /// Object to get Cray Blocking Services.
  CedarCrayServices crab;
  ///
  int called;
  
  /// Internal buffer of data as big as a COS block.
#ifndef CEDAR_USE_MULTITHREAD
  byte cosBlock[SIZE_OF_COS_BLOCK];
#endif // CEDAR_USE_MULTITHREAD
  
  
#ifdef CEDAR_USE_MULTITHREAD

  int val;

  int previous;
  
  int current;
  
  byte *cosBlock;
  
  thread_parameters *pars;
  
  pthread_t * my_thread;

  struct timespec tv;

  int buffer_index;
  
#endif // CEDAR_USE_MULTITHREAD

  /// File handler and stream for the connection.
  ifstream os;
  /// Establish connection with a CBF file.
  int connect();
  /// Breaks connection with a CBF file.
  int disconnect();
  /// Gets 4096 bytes from the file stream a loads the data into cosBlock. 
  int get_cosBlock();
  /// Loads control from data in variable my_word.
  void load_my_control();
  /// Loads a word using data from cosBlock.
  void load_my_word();
  /// calculates if control my_control is BCW, EOR, EOF or EOD.
  void determine_type_of_control();
  ///
  int get_cache_optimal_size();
  ///
  int get_first_CedarBlock();
  ///
  int get_next_CedarBlock();


public: 

  /// Default constructor.
  CedarCrayBlockingFormat(int check_blocks);
  /// Destructor.
  ~CedarCrayBlockingFormat();
  /// Appends a CedarBlock of data to the end of a CBF file.
  int append_CedarBlock (CedarBlock &);

  /// Associates the object with a CBF file.
  virtual void open_file(const char *file_name);

  /**
   *@name Sequencial access.
   * Documentation not ready.
   */
  //@{
    /**
     * Takes as a parameter a reference to a CedarBlock object and loads into it a block of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual const CedarLogicalRecord* get_first_logical_record ();
    /**
     * Takes as a parameter a reference to a CedarBlock object and loads into it a block of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual const CedarLogicalRecord* get_next_logical_record ();
    /**
     * Takes as a parameter a reference to a CedarGroup object and loads into it a group of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual int get_first_CedarGroup (CedarGroup &);
    /**
     * Takes as a parameter a refernce to a CedarGroup object and loads into it a group of data.
     * Returns 1 if the operation was succeful. else returs 0.
     */
          virtual int get_next_CedarGroup  (CedarGroup &);
  
  //@}

  /// Returns 1 when the end of the data set is reached, else returns 0.
  virtual int end_dataset() {return end_of_dataset;}
  ///
  virtual void rewind();

};


#endif // CedarCrayBlockingFormat_h_

