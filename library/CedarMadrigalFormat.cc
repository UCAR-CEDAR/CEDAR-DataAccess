/*******************************************************************
 * CLASS CedarMadrigalFormat - Definition
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

#include <cstring>

#include "CedarMadrigalFormat.h"
#include "CedarGroup.h"
#include "CedarErrorHandler.h"

using std::ios ;
using std::cout ;
using std::endl ;

CedarMadrigalFormat::CedarMadrigalFormat( int check_blocks )
    : end_of_dataset(0), has_name(0), log_counter(0)
{
    if( check_blocks )
	check_sum_on_blocks = 1 ;
    else
	check_sum_on_blocks = 0 ;

    count = 0 ;
}  
 
CedarMadrigalFormat::~CedarMadrigalFormat()
{
}
  
void CedarMadrigalFormat::open_file( const char *file_name )
{
    if( file_name == NULL )
    {
	CedarErrorHandler::errorT( CEDARFILE__EXIT__FILENAME_NULL,
	                           "s",
				   CEDARFILE__FATAL__FILENAME_NULL ) ;
    }
    else
    {
	if( strlen( file_name ) >= MAXFILENAME )
	{
	    CedarErrorHandler::errorT( CEDARFILE__EXIT__FILE_NAME_TOO_LONG,
	                               "s",
				       CEDARFILE__FATAL__FILE_NAME_TOO_LONG ) ;
	}
	else
	{
	    strcpy( name, file_name ) ;
	    has_name = 1 ;
	}
    }
}

inline int
CedarMadrigalFormat::do_checksum()
{
    COUT( cout << __FILE__ << ":" << __LINE__ << " Doing checksum" << endl ; )

    field field_a = total_number_of_significant_bytes / 2 ;
    int how_many = ( total_number_of_significant_bytes / 2 ) - 2 ;

    // Lets calculate the check sum across all the fields in the array
    // but the last one...
    for( int r = 0; r < how_many; r++ )
    {
	field field_b = build_word( r * 2 + 2 ) ;
	field_a = field_a ^ field_b ;
    }

    //now we calculate the check sum with the last field of this CedarBlock
    int check_sum = build_word( total_number_of_significant_bytes - 2 ) ;

    COUT( cout << __FILE__ << ":" << __LINE__ << "check_sum = "
               << check_sum << endl ; )
    COUT( cout << __FILE__ << ":" << __LINE__ << "field_a = "
               << field_a << endl ; )
    if( check_sum == field_a )
    {
	return 1 ;
    }
    else 
    {
	return 0 ;
    }
}

int
CedarMadrigalFormat::load_madrigal_buffer()
{
    memset( buf, (byte)NULL, MADRIGAL_PHYSICAL_RECORD_LENGTH ) ;

    COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"This is call "<<++count<<endl;)

    os.read( (char *)buf, MADRIGAL_PHYSICAL_RECORD_LENGTH ) ;

    if( os.eof() )
    {
	end_of_dataset = 1 ;
	os.close() ;
	return 0 ;
    }

    COUT(
	if( os.bad() ) 
	    cout << __FILE__ << ":" << __LINE__ << " " << "OS bad" << endl ;
    )
    COUT(
	if( os.eof() )
	    cout << __FILE__ << ":" << __LINE__ << " " << "OS eof" << endl ;
    )
    COUT(
	if( os.fail() )
	    cout << __FILE__ << ":" << __LINE__ << " " << "OS fail" << endl ;
    )
    COUT(
	if( os.good() )
	    cout << __FILE__ << ":" << __LINE__ << " " << "OS good" << endl ;
    )

    int i =os.gcount() ;

    COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"Readed "<<i<<" bytes"<<endl;)

    if( i == 0 )
    {
	end_of_dataset = 1 ;
	os.close() ;
	return 0 ;
    }
    else if( i != MADRIGAL_PHYSICAL_RECORD_LENGTH )
    {
	CedarErrorHandler::errorT( CEDARFILE__EXIT__FILE_NOT_OPEN,
	                           "sis",
				   "Can not read data exactly ",
				   MADRIGAL_PHYSICAL_RECORD_LENGTH,
				   " bytes from madrigal file." ) ;
    }
    else
    {
	COUT(
	    cout << __FILE__ << ":" << __LINE__ << " "
	         << "Dataset buffer still OK" << endl ; )
    }

    total_number_of_significant_bytes = build_word( 0 ) * 2 ;
    if( total_number_of_significant_bytes < 0 )
    {
	CedarErrorHandler::errorT( CEDARFILE__EXIT__SIGWORDS_LESS_THAN_0,
				   "s",
				   CEDARFILE__MSG__SIGWORDS_LESS_THAN_0 ) ;
    }

    COUT(
	cout << __FILE__ << ":" << __LINE__ << " "
	     << "Total Number of significant bytes "
	     << total_number_of_significant_bytes << endl ; )

    if( check_sum_on_blocks )
    {
	if( !do_checksum() )
	{
	    CedarErrorHandler::errorT( CEDARFILE__EXIT__BAD_CHECK_SUM,
				       "s",
				       CEDARFILE__FATAL__BAD_CHECK_SUM ) ;
	}

	COUT(else cout<<__FILE__<<":"<<__LINE__<<" "<<"Checksum OK"<<endl;)
    }

    first_word_of_the_first_logical_record_start = build_word( 2 ) ;
    if( first_word_of_the_first_logical_record_start < 0 )
    {
	CedarErrorHandler::errorT( CEDARFILE__EXIT__FIRSTWORD_FIRSTLR_LT_0,
	                           "s",
				   CEDARFILE__MSG__FIRSTWORD_FIRSTLR_LT_0 ) ;
    }


    COUT(
	cout << __FILE__ << ":" << __LINE__ << " "
	     << "First word of the first logical record start "
	     << first_word_of_the_first_logical_record_start << endl ; )

    first_word_of_the_last_logical_record_start = build_word( 4 ) ;
    if( first_word_of_the_last_logical_record_start < 0 )
    {
	CedarErrorHandler::errorT( CEDARFILE__EXIT__FIRSTWORD_LASTLR_LT_0,
			           "s",
				   CEDARFILE__MSG__FIRSTWORD_LASTLR_LT_0 ) ;
    }

    COUT(
	cout << __FILE__ << ":" << __LINE__ << " "
	     << "First word of the last logical record start "
	     << first_word_of_the_last_logical_record_start << endl ; )

    return i ;
}

const CedarLogicalRecord *
CedarMadrigalFormat::get_first_logical_record()
{
    if( has_name )
    {
	os.open( name, ios::binary|ios::in ) ;
	if( !os )
	    return 0 ;   
	else
	{
	    load_madrigal_buffer() ;

	    if( first_word_of_the_first_logical_record_start > 0 )
		buf_marker = first_word_of_the_first_logical_record_start * 2 ;
	    else
		CedarErrorHandler::errorT( CEDARFILE__EXIT__FIRSTWORD_FIRSTLR_SET_0,
				       "s",
				       CEDARFILE__MSG__FIRSTWORD_FIRSTLR_SET_0 ) ;
	}

	int number_of_bytes_for_this_logical_record = -1 ;

	if( buf_marker < total_number_of_significant_bytes )
	{
	    number_of_bytes_for_this_logical_record = build_word( buf_marker ) * 2 ;
	}
	else
	{
	    if( !end_of_dataset )
	    {
		load_madrigal_buffer() ;
		number_of_bytes_for_this_logical_record
		    = build_word( buf_marker ) * 2 ;
	    }
	}

	if( number_of_bytes_for_this_logical_record < 0 )
	{
	    CedarErrorHandler::errorT( CEDARFILE__EXIT__LENGTH_FIRSTLR_LT_0,
				       "s",
				       CEDARFILE__MSG__LENGTH_FIRSTLR_LT_0 ) ;
	}

	COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"Number of bytes in this logical record "<<number_of_bytes_for_this_logical_record<<endl;)
	COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"The buf marker is "<<buf_marker<<endl;)

	int did_partial_load = 0 ;

	for( int i = 0; i < number_of_bytes_for_this_logical_record; i++ ) 
	{
	    record.crData[i] = buf[buf_marker++] ;
	    if( buf_marker >= total_number_of_significant_bytes - 2 )
	    {
		if( !end_of_dataset )
		{
		    COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"calling partial load The buf marker is "<<buf_marker<<endl;)
		    if( !load_madrigal_buffer() )
		    {
			return 0 ;
		    }
		    COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"loaded so far is "<<i+1<<endl;)
		    buf_marker = 6 ;
		    did_partial_load = 1 ;
		}
	    }
	}

	if( did_partial_load )
	{
	    COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"Did partial load, The buf marker is before "<<buf_marker<<endl;)
	    buf_marker = first_word_of_the_first_logical_record_start * 2 ;
	}

	COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"The buf marker is "<<buf_marker<<endl;)
	COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"returning logical record number "<<++log_counter<<endl;) 

	return record.get_record() ;
    }
    return 0;
}

const CedarLogicalRecord* CedarMadrigalFormat::get_next_logical_record()
{
  if(!end_of_dataset)
    {
      
      int number_of_bytes_for_this_logical_record;

      COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"The buf marker is "<<buf_marker<<endl;)

      if(buf_marker==0)
	{
	  if (!end_of_dataset)
	    {
	      if(!load_madrigal_buffer())
		return 0;
	    }
	      
	  if (first_word_of_the_first_logical_record_start>0)
	    buf_marker=first_word_of_the_first_logical_record_start*2;

	  COUT(else if (first_word_of_the_first_logical_record_start==0) cout<<"0 data"<<endl;)
		
	  else
	    CedarErrorHandler::errorT(105,"s","Garbage buffer!");
	  
	  number_of_bytes_for_this_logical_record=build_word(buf_marker)*2;
	}
      else if(buf_marker>total_number_of_significant_bytes)
	{
	  if (!end_of_dataset)
	    {
	      if(!load_madrigal_buffer())
		return 0;
	    }
	      
	  if (first_word_of_the_first_logical_record_start>0)
	    buf_marker=first_word_of_the_first_logical_record_start*2;
	  
	  COUT(else if (first_word_of_the_first_logical_record_start==0) cout<<"0 data"<<endl;)

	  else
	    CedarErrorHandler::errorT(105,"s","Garbage buffer!");
	  
	  number_of_bytes_for_this_logical_record=build_word(buf_marker)*2;
	}
      else
	{
	  number_of_bytes_for_this_logical_record=build_word(buf_marker)*2;
	  if (number_of_bytes_for_this_logical_record==0)
	    {
	      if (!end_of_dataset)
		{
		  COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"calling partial load The buf marker is "<<buf_marker<<endl;)
		  if(!load_madrigal_buffer())
		    return 0;
		  buf_marker=6;
		}
	    }
	}

      if (number_of_bytes_for_this_logical_record<0)
	CedarErrorHandler::errorT(105,"s","Length of the first logical record smaller than 0");
      
      
      COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"Number of bytes in this logical record "<<number_of_bytes_for_this_logical_record<<endl;)
      COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"The buf marker is "<<buf_marker<<endl;)
      
      int did_partial_load=0;
      
      for (int i=0; i<number_of_bytes_for_this_logical_record; i++) 
	{
	  record.crData[i]=buf[buf_marker++];
	  if (buf_marker>=total_number_of_significant_bytes-2)
	    {
	      if (!end_of_dataset)
		{
		  COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"calling partial load The buf marker is "<<buf_marker<<endl;)
		  if(!load_madrigal_buffer())
		    CedarErrorHandler::errorT(105,"s","Can not get more data, imcomplete logical record");
		  buf_marker=6;
		  COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"loaded so far is "<<i+1<<endl;)
		  did_partial_load=1;
		}
	    }
	}
      
      if(did_partial_load)
	{
	  COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"Did partial load, The buf marker is before "<<buf_marker<<endl;)
	  buf_marker=first_word_of_the_first_logical_record_start*2;
	}

      COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"The buf marker is "<<buf_marker<<endl;)
      COUT(cout<<__FILE__<<":"<<__LINE__<<" "<<"returning logical record number "<<++log_counter<<endl;) 

      return record.get_record();
    }

  return 0;

}

int CedarMadrigalFormat::get_first_CedarGroup (CedarGroup &)
{
    return -1 ;
}

int CedarMadrigalFormat::get_next_CedarGroup  (CedarGroup &)
{
    return -1 ;
}

void CedarMadrigalFormat::rewind()
{
  os.close();
}
