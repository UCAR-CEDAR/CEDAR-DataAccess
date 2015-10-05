/*******************************************************************
 * CLASS CedarCrayBlockingFormat - Definition
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

#include <iostream>
#include <cstring>

using std::ios ;
using std::cerr ;
using std::endl ;

#include "CedarCrayBlockingFormat.h"
#include "CedarErrorHandler.h"
#ifdef LOGGING_WITH_CEDARDUMP
#include "CedarDump.h"
#endif

CedarCrayBlockingFormat::CedarCrayBlockingFormat(int check_blocks)
{
  plogrec=0;
  if(check_blocks)
    check_sum_on_blocks=1;
  else
    check_sum_on_blocks=0;

  block_number=0;
  connected=0;
  has_name=0;
  can_get_more=0;
  end_of_dataset=1;
  called=0;

#ifdef CEDAR_USE_MULTITHREAD
  cosBlock=0;
  pars=0;
  my_thread=0;
  current=-1;
  val=0;
  tv.tv_sec=0;
  tv.tv_nsec=2;
#endif

#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__1);
      CedarDump::Dumper()<<CEDARFILE__MSG__OBJECT_CONSTRUCTED;
      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__1);
#endif
}

CedarCrayBlockingFormat::~CedarCrayBlockingFormat()
{
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__2);
      CedarDump::Dumper()<<CEDARFILE__MSG__DESTRUCTING_OBJECT;
      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__2);
#endif
  CedarCrayBlockingFormat::disconnect();
}

void CedarCrayBlockingFormat::open_file(const char *file_name)
{
#ifdef LOGGING_WITH_CEDARDUMP  
      CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__4);
      CedarDump::Dumper()<<CEDARFILE__MSG__GIVING_NAME;
#endif
  if (connected)
    {
#ifdef LOGGING_WITH_CEDARDUMP
	CedarDump::Dumper()<<CEDARFILE__MSG__CHANGING_NAME<<name<<ENDL; 
#endif
      disconnect();
      has_name=0;
    }
  if (file_name==NULL)
    {
      CedarErrorHandler::errorT(CEDARFILE__EXIT__FILENAME_NULL,"s",CEDARFILE__FATAL__FILENAME_NULL);
    }
  else
    {
      if (strlen(file_name)>=MAXFILENAME)
	{
	  CedarErrorHandler::errorT(CEDARFILE__EXIT__FILE_NAME_TOO_LONG,"s",CEDARFILE__FATAL__FILE_NAME_TOO_LONG);
	}
      else
	{
	  strcpy(name,file_name);
	  has_name=1;
	}
    }
#ifdef LOGGING_WITH_CEDARDUMP  
    CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__4);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//
//                              BEGIN MULTITHREAD READ AHEAD
//
//
//  The functions connect(), disconnect(), get_cosBlock() will manipulate
//  a cedar file in a different way if the library is compiled to use a thread
//  to read ahead cache buffers. The function get_cache_optimal_size() is
//  auxiliary and the function read_ahead(...) is the thread.
//
//  November 11, 2000
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifdef CEDAR_USE_MULTITHREAD

inline int CedarCrayBlockingFormat::get_cache_optimal_size()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__9);
#endif
  // We protect the CEDAR API from computers where the maximum size that 
  // the iostream library can read in a istream& istream::read (pointer, int len)
  // call is smaller than 128 cosBlock(s). Tipically this is for machines where
  // an integer is two bytes.
  if (SSIZE_MAX<(128*SIZE_OF_COS_BLOCK))
    CedarErrorHandler::errorT(CEDARFILE__EXIT__NOT_SUPPORTED_CACHE ,"s",CEDARFILE__FATAL__NOT_SUPPORTED_CACHE);
  struct stat file_info;
  if (stat(name,&file_info))
    CedarErrorHandler::errorT(CEDARFILE__EXIT__CAN_NOT_GET_FILE_STAT,"s",CEDARFILE__FATAL__CAN_NOT_GET_FILE_STAT);
  else
    val=file_info.st_size/SIZE_OF_COS_BLOCK;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper()<<CEDARFILE__MSG__NUMBER_COS_BLOCKS1<<val<<CEDARFILE__MSG__NUMBER_COS_BLOCKS2<<ENDL;
  CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__9);
#endif
  if (val>128)
    return 128;
  else
    return val;

}

inline int CedarCrayBlockingFormat::connect()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__3);
#endif
  if (has_name)
    {
      if (!connected)
	{
	  os.open (name,ios::binary|ios::in);
	  if (!os)
	    {
#ifdef LOGGING_WITH_CEDARDUMP
	      CedarDump::Dumper()<<CEDARFILE__MSG__COULD_NOT_CONNECT<<name<<ENDL;
	      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__3);
#endif
	      return 0;   
	    }
	  else 
	    {
#ifdef LOGGING_WITH_CEDARDUMP
	      CedarDump::Dumper()<<CEDARFILE__MSG__COULD_CONNECT<<name<<ENDL; 
	      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__3);
#endif
	      connected=1;

	      pars = new thread_parameters;
	      pars->pos=&os;
	      pars->os_status=1;
	      pars->number_of_read_ahead_buffers=get_cache_optimal_size();
	      pars->buffers=  new  struct read_ahead_buffer [pars->number_of_read_ahead_buffers];
	      pars->buffers[0].buf=new byte [SIZE_OF_COS_BLOCK*pars->number_of_read_ahead_buffers];
	      memset(pars->buffers[0].buf,(byte)NULL, SIZE_OF_COS_BLOCK * pars->number_of_read_ahead_buffers);
	      pars->pos->read(pars->buffers[0].buf, SIZE_OF_COS_BLOCK * pars->number_of_read_ahead_buffers);

	      if (val>6400) // Create thread for files only larger than 25 Megabytes 
		{
		  pars->buffers[0].used=0;
		  pars->q.push(0);
		  for (int r=1; r<pars->number_of_read_ahead_buffers; r++)
		    {
		      pars->buffers[r].buf=pars->buffers[0].buf+(SIZE_OF_COS_BLOCK*r);
		      pars->buffers[r].used=0;
		      pars->q.push(r);
		    }
		  
		  if (*pars->pos) // Create the thread only is there is data to read from the ifstream "os"
		    {
		      
		      my_thread=new pthread_t();
		      pars->number_of_wait=0;
		      pars->mutex=new pthread_mutex_t();
		      pthread_mutex_init(pars->mutex,NULL);
		      pars->running=1;
#ifdef LOGGING_WITH_CEDARDUMP
		      pars->pdumper=&CedarDump::Dumper();
#endif
		      if (pthread_create(my_thread, NULL, read_ahead, (void*)pars))
			CedarErrorHandler::errorT(CEDARFILE__EXIT__CAN_NOT_CREATE_READ_AHEAD_THREAD,"s",CEDARFILE__FATAL__CAN_NOT_CREATE_READ_AHEAD_THREAD);
		    }
		}
	      else
		{
		  for (int r=1; r<pars->number_of_read_ahead_buffers; r++)
		    pars->buffers[r].buf=pars->buffers[0].buf+(SIZE_OF_COS_BLOCK*r);
		  buffer_index=0;
		}
	      return 1;
	    }
	}
    }
  else
    {
#ifdef LOGGING_WITH_CEDARDUMP   
      CedarDump::Dumper()<<CEDARFILE__MSG__CAN_NOT_CONNECT_OBJECT_IS_NOT_RELATED_TO_CBF_FILE;
      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__3);
#endif
      return 0;
    }
return 0;
}

int CedarCrayBlockingFormat::disconnect()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__10);
#endif

  if (connected)
    {
      os.close();
      connected=0;
      if(my_thread)
	{
	  pthread_mutex_lock(pars->mutex);
	  pars->running=0;
	  assert(!pars->running);
	  pthread_mutex_unlock(pars->mutex);
	  assert(!pthread_join(*my_thread, NULL));
	  delete my_thread;
	  pthread_mutex_destroy(pars->mutex);
	  delete pars->mutex;
#ifdef LOGGING_WITH_CEDARDUMP
	  CedarDump::Dumper()<<CEDARFILE__MSG__WAIT_THREAD1<<pars->number_of_wait<<CEDARFILE__MSG__WAIT_THREAD2<<endl;
#endif
	}

      delete [] pars->buffers[0].buf;
      pars->buffers[0].buf=0;
      delete [] pars->buffers;
      pars->buffers=0;
      delete pars;
      pars=0;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__10);
#endif
      return 1;
    }
  else return 0;
}

void* read_ahead(thread_parameters *pars)
{
  //cerr<<"Reading ahead"<<endl;

#ifdef LOGGING_WITH_CEDARDUMP
  (*pars->pdumper)<<CEDARFILE__MSG__READ_THREAD<<endl;
#endif
  register int i=0;
  int should_exit=0;
  register int t_max=pars->number_of_read_ahead_buffers;
  register int t;
  for (;;)
    {
      pthread_mutex_lock(pars->mutex);
      if (!pars->running)
	// Do not exit right away so we can unlock the mutex
	should_exit=1;
      pthread_mutex_unlock(pars->mutex);

      if(should_exit)
	{
#ifdef LOGGING_WITH_CEDARDUMP  
	  (*pars->pdumper)<<CEDARFILE__MSG__READ_THREAD_EXITING<<endl; 
#endif
	  pthread_exit(0);
	}

      for (t=0; t<t_max; t++)
	{
	  if ( pars->buffers[t].used )
	    {
	      if(*pars->pos)
		{
		  pars->pos->read( pars->buffers[t].buf, SIZE_OF_COS_BLOCK);
		  i=pars->pos->gcount();
		  
#ifdef LOGGING_WITH_CEDARDUMP
		  (*pars->pdumper)<<CEDARFILE__MSG__NUMBER_BYTES<<i<<ENDL;
		  (*pars->pdumper)<<CEDARFILE__MSG__STATUS_READ_OS;
		  if (!(*pars->pos))
		    {
		      (*pars->pdumper)<<0<<ENDL;
		      if (pars->pos->bad()) 
			(*pars->pdumper)<<CEDARFILE__MSG__BAD_BIT_TRUE;
		      if (pars->pos->eof())
			(*pars->pdumper)<<CEDARFILE__MSG__EOF_BIT_TRUE;
		      if (pars->pos->fail())
			(*pars->pdumper)<<CEDARFILE__MSG__FAIL_BIT_TRUE;
		    }
		  else
		    { 
		      (*pars->pdumper)<<1<<ENDL; 
		      if (pars->pos->good()) 
			(*pars->pdumper)<<CEDARFILE__MSG__GOOD_BIT_TRUE;
		    }
#endif
		  
		  while (i<4096)
		    {
		      pars->buffers[t].buf[i]=(byte)NULL;
		      i++;
		    }
		  pthread_mutex_lock(pars->mutex);
		  pars->q.push(t);
		  pars->buffers[t].used=0;
		  if (!(*pars->pos))
		    {
		      pars->os_status=0;
		      pthread_mutex_unlock(pars->mutex);
		      pthread_exit(0);
		      break;
		    }
		  pthread_mutex_unlock(pars->mutex);
		}
	    }
	}
    }
}


inline int CedarCrayBlockingFormat::get_cosBlock()
{
#ifdef LOGGING_WITH_CEDARDUMP
  called++;
  CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__5);
  CedarDump::Dumper()<<CEDARFILE__MSG__GETTING_BLOCK<<called<<ENDL;
#endif

  if(my_thread)
    {
      previous=current;
      
      if(pars->os_status)
	{
	  while(pars->q.empty())
	    {
	      pars->number_of_wait++;
	      nanosleep(&tv,0);
	    }
	}
      if(!pars->q.empty())
	{
	  
	  current=pars->q.front();
	  
	  pthread_mutex_lock(pars->mutex);
	  pars->q.pop();
	  if(previous>-1)
	    pars->buffers[previous].used=1;
	  pthread_mutex_unlock(pars->mutex);
	  
	  cosBlock=pars->buffers[current].buf;
	  
	  block_counter=0;
	  return 1;
	}
      else
	return 0;
    }
  else
    {
      if (buffer_index>=pars->number_of_read_ahead_buffers)
	{
	  if (os)
	    {
	      memset(pars->buffers[0].buf,(byte)NULL, SIZE_OF_COS_BLOCK * pars->number_of_read_ahead_buffers);
	      os.read(pars->buffers[0].buf, SIZE_OF_COS_BLOCK * pars->number_of_read_ahead_buffers);
	      for (int r=1; r<pars->number_of_read_ahead_buffers; r++)
		pars->buffers[r].buf=pars->buffers[0].buf+(SIZE_OF_COS_BLOCK*r);
	      
#ifdef LOGGING_WITH_CEDARDUMP
	      CedarDump::Dumper()<<CEDARFILE__MSG__NUMBER_BYTES<<os.gcount()<<ENDL;
	      CedarDump::Dumper()<<CEDARFILE__MSG__STATUS_READ_OS;
	      if (!os)
		{
		  CedarDump::Dumper()<<0<<ENDL;
		  if (pars->pos->bad()) 
		    CedarDump::Dumper()<<CEDARFILE__MSG__BAD_BIT_TRUE;
		  if (pars->pos->eof())
		    CedarDump::Dumper()<<CEDARFILE__MSG__EOF_BIT_TRUE;
		  if (pars->pos->fail())
		    CedarDump::Dumper()<<CEDARFILE__MSG__FAIL_BIT_TRUE;
		}
	      else
		{ 
		  CedarDump::Dumper()<<1<<ENDL; 
		  if (pars->pos->good()) 
		    CedarDump::Dumper()<<CEDARFILE__MSG__GOOD_BIT_TRUE;
		}
#endif
	      buffer_index=0;
	    }
	  else
	    return 0;
	}
      cosBlock=pars->buffers[buffer_index++].buf;
      block_counter=0;
      return 1;
    }
}

//////////////////////////////////////////////////
// 
// Not multi-thread functions start here 
//
//////////////////////////////////////////////////


#else // #ifdef CEDAR_USE_MULTITHREAD

int CedarCrayBlockingFormat::connect()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__3);
#endif
  if (has_name)
    {
      if (!connected)
	{
	  os.open (name,ios::binary|ios::in);
	  if (!os)
	    {
#ifdef LOGGING_WITH_CEDARDUMP
	      CedarDump::Dumper()<<CEDARFILE__MSG__COULD_NOT_CONNECT<<name<<ENDL;
	      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__3);
#endif
	      return 0;   
	    }
	  else 
	    {
#ifdef LOGGING_WITH_CEDARDUMP
	      CedarDump::Dumper()<<CEDARFILE__MSG__COULD_CONNECT<<name<<ENDL; 
	      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__3);
#endif
	      connected=1;
	      return 1;
	    }
	}
    }
  else
    {
#ifdef LOGGING_WITH_CEDARDUMP   
      CedarDump::Dumper()<<CEDARFILE__MSG__CAN_NOT_CONNECT_OBJECT_IS_NOT_RELATED_TO_CBF_FILE;
      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__3);
#endif
      return 0;
    }
return 0;
}

int CedarCrayBlockingFormat::disconnect()
{
  if (connected)
    {
      os.close();
      connected=0;
      return 1;
    }
  else return 0;
}

int CedarCrayBlockingFormat::get_cosBlock()
{
#ifdef LOGGING_WITH_CEDARDUMP
  called++;
  CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__5);
  CedarDump::Dumper()<<CEDARFILE__MSG__GETTING_BLOCK<<called<<ENDL;
#endif
  int i=0;
  os.read((char *)cosBlock, sizeof cosBlock);
  i=os.gcount();
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper()<<CEDARFILE__MSG__NUMBER_BYTES<<i<<ENDL;
  CedarDump::Dumper()<<CEDARFILE__MSG__STATUS_READ_OS;
  if (!os)
    {
      CedarDump::Dumper()<<0<<ENDL;
      if (os.bad()) 
	CedarDump::Dumper()<<CEDARFILE__MSG__BAD_BIT_TRUE;
      if (os.eof())
	CedarDump::Dumper()<<CEDARFILE__MSG__EOF_BIT_TRUE;
      if (os.fail())
	CedarDump::Dumper()<<CEDARFILE__MSG__FAIL_BIT_TRUE;
    }
  else
    { 
      CedarDump::Dumper()<<1<<ENDL; 
      if (os.good()) 
	CedarDump::Dumper()<<CEDARFILE__MSG__GOOD_BIT_TRUE;
    }
#endif
  while (i<4096)
    {
      cosBlock[i]=(byte)NULL;
      i++;
    }
  block_counter=0;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__5);
#endif
  if (!os) 
    {
      return 0;
    }
  return 1;
}

#endif // CEDAR_USE_MULTITHREAD

/////////////////////////////////////////////////////////////////////////////////////////
//
//
//                              END MULTITHREAD READ AHEAD
//
//
/////////////////////////////////////////////////////////////////////////////////////////



void CedarCrayBlockingFormat::load_my_word()
{
  for (int j=0; j<8; j++)
    {
      switch (j){
      case 0 :
	my_word.b7  =crab.get_bit(cosBlock[j+block_counter],0); my_word.b6  =crab.get_bit(cosBlock[j+block_counter],1);	
	my_word.b5  =crab.get_bit(cosBlock[j+block_counter],2); my_word.b4  =crab.get_bit(cosBlock[j+block_counter],3);
	my_word.b3  =crab.get_bit(cosBlock[j+block_counter],4); my_word.b2  =crab.get_bit(cosBlock[j+block_counter],5);	
	my_word.b1  =crab.get_bit(cosBlock[j+block_counter],6); my_word.b0  =crab.get_bit(cosBlock[j+block_counter],7);
	break;
      case 1 :
	my_word.b15 =crab.get_bit(cosBlock[j+block_counter],0); my_word.b14 =crab.get_bit(cosBlock[j+block_counter],1);	
	my_word.b13 =crab.get_bit(cosBlock[j+block_counter],2); my_word.b12 =crab.get_bit(cosBlock[j+block_counter],3);
	my_word.b11 =crab.get_bit(cosBlock[j+block_counter],4); my_word.b10 =crab.get_bit(cosBlock[j+block_counter],5);	
	my_word.b9  =crab.get_bit(cosBlock[j+block_counter],6); my_word.b8  =crab.get_bit(cosBlock[j+block_counter],7);
	break;
      case 2 :
	my_word.b23 =crab.get_bit(cosBlock[j+block_counter],0); my_word.b22 =crab.get_bit(cosBlock[j+block_counter],1);	
	my_word.b21 =crab.get_bit(cosBlock[j+block_counter],2); my_word.b20 =crab.get_bit(cosBlock[j+block_counter],3);
	my_word.b19 =crab.get_bit(cosBlock[j+block_counter],4); my_word.b18 =crab.get_bit(cosBlock[j+block_counter],5);	
	my_word.b17 =crab.get_bit(cosBlock[j+block_counter],6); my_word.b16 =crab.get_bit(cosBlock[j+block_counter],7);
	break;
      case 3 :
	my_word.b31 =crab.get_bit(cosBlock[j+block_counter],0); my_word.b30 =crab.get_bit(cosBlock[j+block_counter],1);	
	my_word.b29 =crab.get_bit(cosBlock[j+block_counter],2); my_word.b28 =crab.get_bit(cosBlock[j+block_counter],3);
	my_word.b27 =crab.get_bit(cosBlock[j+block_counter],4); my_word.b26 =crab.get_bit(cosBlock[j+block_counter],5);	
	my_word.b25 =crab.get_bit(cosBlock[j+block_counter],6); my_word.b24 =crab.get_bit(cosBlock[j+block_counter],7);
	break;
      case 4 :
	my_word.b39 =crab.get_bit(cosBlock[j+block_counter],0); my_word.b38 =crab.get_bit(cosBlock[j+block_counter],1);	
	my_word.b37 =crab.get_bit(cosBlock[j+block_counter],2); my_word.b36 =crab.get_bit(cosBlock[j+block_counter],3);
	my_word.b35 =crab.get_bit(cosBlock[j+block_counter],4); my_word.b34 =crab.get_bit(cosBlock[j+block_counter],5);	
	my_word.b33 =crab.get_bit(cosBlock[j+block_counter],6); my_word.b32 =crab.get_bit(cosBlock[j+block_counter],7);
	break;
      case 5 :
	my_word.b47 =crab.get_bit(cosBlock[j+block_counter],0); my_word.b46 =crab.get_bit(cosBlock[j+block_counter],1);	
	my_word.b45 =crab.get_bit(cosBlock[j+block_counter],2); my_word.b44 =crab.get_bit(cosBlock[j+block_counter],3);
	my_word.b43 =crab.get_bit(cosBlock[j+block_counter],4); my_word.b42 =crab.get_bit(cosBlock[j+block_counter],5);	
	my_word.b41 =crab.get_bit(cosBlock[j+block_counter],6); my_word.b40 =crab.get_bit(cosBlock[j+block_counter],7);
	break;
      case 6 :
	my_word.b55 =crab.get_bit(cosBlock[j+block_counter],0); my_word.b54 =crab.get_bit(cosBlock[j+block_counter],1);	
	my_word.b53 =crab.get_bit(cosBlock[j+block_counter],2); my_word.b52 =crab.get_bit(cosBlock[j+block_counter],3);
	my_word.b51 =crab.get_bit(cosBlock[j+block_counter],4); my_word.b50 =crab.get_bit(cosBlock[j+block_counter],5);	
	my_word.b49 =crab.get_bit(cosBlock[j+block_counter],6); my_word.b48 =crab.get_bit(cosBlock[j+block_counter],7);
	break;
      case 7 :
	my_word.b63 =crab.get_bit(cosBlock[j+block_counter],0); my_word.b62 =crab.get_bit(cosBlock[j+block_counter],1);	
	my_word.b61 =crab.get_bit(cosBlock[j+block_counter],2); my_word.b60 =crab.get_bit(cosBlock[j+block_counter],3);
	my_word.b59 =crab.get_bit(cosBlock[j+block_counter],4); my_word.b58 =crab.get_bit(cosBlock[j+block_counter],5);	
	my_word.b57 =crab.get_bit(cosBlock[j+block_counter],6); my_word.b56 =crab.get_bit(cosBlock[j+block_counter],7);
	break;
      }
    }
  block_counter=block_counter+8;
}


void CedarCrayBlockingFormat::load_my_control()
{
      load_my_word();
      determine_type_of_control();
      if (my_control.type_of_control==cray_BCW)
	{
	  crab.load_block_control(my_control, my_word);
	}
      else
	{
	  crab.load_record_control (my_control, my_word);
	}
      if (my_control.forward<0)
	CedarErrorHandler::errorT(CEDARFILE__EXIT__INVALID_FORWARD_INDEX,"sis",CEDARFILE__FATAL__INVALID_FORWARD_INDEX,my_control.forward,ENDL);
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__8);
      CedarDump::Dumper()<<CEDARFILE__MSG__BLOCK_COUNTER_IN_POSITION<<block_counter<<ENDL;
      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__8);
#endif
}

void CedarCrayBlockingFormat::determine_type_of_control()
{
  int typ=crab.calculate_M_on_word (my_word);
  switch (typ)
    {
    case 0:
      my_control.type_of_control=cray_BCW;
      break;
    case 8:
      my_control.type_of_control=cray_EOR;
      break;
    case 14:
      my_control.type_of_control=cray_EOF;
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper()<<CEDARFILE__MSG__EOF_FOUND;
#endif
      break;
    case 15:
      my_control.type_of_control=cray_EOD;
      break;
    default:
#ifdef LOGGING_WITH_CEDARDUMP
      crab.show_word(my_word);      
#endif
      CedarErrorHandler::errorT(CEDARFILE__EXIT__TYPE_OF_CONTROL,"s",CEDARFILE__FATAL__TYPE_OF_CONTROL);
      break;
    }
}


int CedarCrayBlockingFormat::get_first_CedarBlock()
{
#ifdef LOGGING_WITH_CEDARDUMP 
  CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__6);
#endif  
  int return_status=0;
  if (connected) disconnect();
  if(connect())
    {
      end_of_dataset=0;
      int m=0;
      register int bytes_to_next_record;
      //register int bytes_consumed;
      can_get_more=get_cosBlock();
      if (can_get_more) load_my_control();
      while (can_get_more&&(my_control.type_of_control!=cray_EOR)&&(my_control.type_of_control!=cray_EOD))
	{
      	  //bytes_consumed=0;
	  bytes_to_next_record=(my_control.forward*8);
	  //while(bytes_consumed<bytes_to_next_record)
	  //{
	  //  cdBlock.crData[m]=cosBlock[block_counter];
	  //   m++;block_counter++;bytes_consumed++;
	  // }

	  if(cdBlock.crData.get_size()<(m+bytes_to_next_record))
	    {
	      int new_size=cdBlock.crData.get_size()+4096;
	      cdBlock.crData.set_size(new_size);
	    }
	  memcpy(((byte*)cdBlock.crData.expose_buffer())+m,cosBlock+block_counter,bytes_to_next_record);
	  m+=bytes_to_next_record;
	  block_counter+=bytes_to_next_record;
	  if (!(block_counter<4096))
	    {
	      can_get_more=get_cosBlock();
	      load_my_control();
	    }
	  else load_my_control();
	}

      // This portion of code address the problem when the creator of the file
      // did not follow the standard for COS blocking. In this cases, cbf files
      // are not multiple of 4096 bytes, thus we can reach the end of the stream
      // without having a full block loaded in the cosBlock.
      // At this point, we are done reading but the exit condition may be that we 
      // reached the end of the stream. In this case we must get sure that there is 
      // not data sitting on the cosBlock.
      // BEGIN PATCH 
      if (!can_get_more && (block_counter<4096))
	{
	  do
	    {
	      //bytes_consumed=0;
	      bytes_to_next_record=(my_control.forward*8);
	      //while(bytes_consumed<bytes_to_next_record)
	      //	{
	      //	  cdBlock.crData[m]=cosBlock[block_counter];
	      //	  m++;block_counter++;bytes_consumed++;
	      //	}
	      if(cdBlock.crData.get_size()<(m+bytes_to_next_record))
		{
		  int new_size=cdBlock.crData.get_size()+4096;
		  cdBlock.crData.set_size(new_size);
		}
	      memcpy(((byte*)cdBlock.crData.expose_buffer())+m,cosBlock+block_counter,bytes_to_next_record);
	      m+=bytes_to_next_record;
	      block_counter+=bytes_to_next_record;
	      load_my_control();
	      if (!(block_counter<4096) && (my_control.type_of_control!=cray_EOD))
		CedarErrorHandler::errorT(CEDARFILE__EXIT__MUST_BE_END_OF_DATASET,"s",CEDARFILE__FATAL__MUST_BE_END_OF_DATASET);
	    }  while (((my_control.type_of_control!=cray_EOR)&&my_control.type_of_control!=cray_EOD));
	}
      // END PATCH

      cdBlock.value=m;
      block_number=1;
      if ((my_control.type_of_control==cray_EOD) || (!can_get_more)) end_of_dataset=1;
      if (check_sum_on_blocks)
	{
	  int block_check_sum_OK=cdBlock.do_block_checksum();
	  if (!my_control.record_control.BDF && (m>0) && block_check_sum_OK) 
	    return_status=1;
	  else if (!block_check_sum_OK)
	    CedarErrorHandler::errorT(CEDARFILE__EXIT__BAD_CHECK_SUM,"s",CEDARFILE__FATAL__BAD_CHECK_SUM);
	}
      else
	{
	  if (!my_control.record_control.BDF && (m>0)) 
	    return_status=1;
	}   
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper()<<CEDARFILE__MSG__BLOCK_BUFFER_IS<<cdBlock.crData.get_size()<<CEDARFILE__MSG__BYTE_UNIT<<ENDL;
      CedarDump::Dumper()<<CEDARFILE__MSG__RECORD_SIZE_IS<<cdBlock.value<<CEDARFILE__MSG__BYTE_UNIT<<ENDL;
      CedarDump::Dumper()<<CEDARFILE__MSG__THIS_FUNCTION_RETURN<<return_status<<ENDL;
      CedarDump::Dumper()<<CEDARFILE__MSG__RECORD_NUMBER_IS<<block_number<<ENDL;
      CedarDump::Dumper()<<CEDARFILE__MSG__DATASET_FLAG<<end_of_dataset<<ENDL;
      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__6);
#endif
      return return_status;
    }
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper()<<CEDARFILE__MSG__THIS_FUNCTION_RETURN<<return_status<<ENDL;
  CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__6);
#endif 
  return return_status;
}

int CedarCrayBlockingFormat::get_next_CedarBlock()
{
#ifdef LOGGING_WITH_CEDARDUMP 
    CedarDump::Dumper().puthead(CEDARFILE__PROTOTYPE__7);
#endif
  int return_status=0;
  if (connected)
    {
      int m=0;
      register int bytes_to_next_record;
      if(can_get_more)
	{
	  do
	    {
	      bytes_to_next_record=(my_control.forward*8);
	      if(cdBlock.crData.get_size()<(m+bytes_to_next_record))
		{
  		  int new_size=cdBlock.crData.get_size()+4096;
  		  cdBlock.crData.set_size(new_size);
  		}
  	      memcpy(((byte*)cdBlock.crData.expose_buffer())+m,cosBlock+block_counter,bytes_to_next_record);
  	      m+=bytes_to_next_record;
  	      block_counter+=bytes_to_next_record;
	      if (!(block_counter<4096))
		{
		  can_get_more=get_cosBlock();
		  load_my_control();
		}
	      else load_my_control();
	    }  while ((my_control.type_of_control!=cray_EOR)&&(can_get_more)&&(my_control.type_of_control!=cray_EOD));
	}
      
      // This portion of code address the problem when the creator of the file
      // did not follow the standard for COS blocking. In this cases, cbf files
      // are not multiple of 4096 bytes, thus we can reach the end of the stream
      // without having a full block loaded in the cosBlock.
      // At this point, we are done reading but the exit condition may be that we 
      // reached the end of the stream. In this case we must get sure that there is 
      // not data sitting on the cosBlock.
      // BEGIN PATCH 
      if (!can_get_more && (block_counter<4096))
	{
	  do
	    {
	      bytes_to_next_record=(my_control.forward*8);
	      if(cdBlock.crData.get_size()<(m+bytes_to_next_record))
		{
  		  int new_size=cdBlock.crData.get_size()+4096;
  		  cdBlock.crData.set_size(new_size);
  		}
  	      memcpy(((byte*)cdBlock.crData.expose_buffer())+m,cosBlock+block_counter,bytes_to_next_record);
  	      m+=bytes_to_next_record;
  	      block_counter+=bytes_to_next_record;
	      load_my_control();
	      if (!(block_counter<4096) && (my_control.type_of_control!=cray_EOD))
		CedarErrorHandler::errorT(CEDARFILE__EXIT__MUST_BE_END_OF_DATASET,"s",CEDARFILE__FATAL__MUST_BE_END_OF_DATASET);
	    }  while (((my_control.type_of_control!=cray_EOR)&&my_control.type_of_control!=cray_EOD));
	}
      // END PATCH
      
      cdBlock.value=m;
      block_number++;
      if ((my_control.type_of_control==cray_EOD) || (!can_get_more)) 
	end_of_dataset=1;
      if (check_sum_on_blocks)
	{
	  int block_check_sum_OK=cdBlock.do_block_checksum();
	  if (!my_control.record_control.BDF && (m>0) && block_check_sum_OK) 
	    return_status=1;
	  else if (!block_check_sum_OK)
	    CedarErrorHandler::errorT(CEDARFILE__EXIT__BAD_CHECK_SUM,"s",CEDARFILE__FATAL__BAD_CHECK_SUM);
	}
      else
	{
	  if (!my_control.record_control.BDF && (m>0)) 
	    return_status=1;
	}
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper()<<CEDARFILE__MSG__BLOCK_BUFFER_IS<<cdBlock.crData.get_size()<<CEDARFILE__MSG__BYTE_UNIT<<ENDL;
      CedarDump::Dumper()<<CEDARFILE__MSG__RECORD_SIZE_IS<<cdBlock.value<<CEDARFILE__MSG__BYTE_UNIT<<ENDL;
      CedarDump::Dumper()<<CEDARFILE__MSG__THIS_FUNCTION_RETURN<<return_status<<ENDL;
      CedarDump::Dumper()<<CEDARFILE__MSG__RECORD_NUMBER_IS<<block_number<<ENDL;
      CedarDump::Dumper()<<CEDARFILE__MSG__DATASET_FLAG<<end_of_dataset<<ENDL;
      CedarDump::Dumper().puttail(CEDARFILE__PROTOTYPE__7);
#endif
      return return_status;
    }
  else
    {
      /**
       * This error is happens mainly because get_first_CedarBlock has not been used before get_first_CedarBlock.
       * We send a little hint to the user.
       */ 
      CedarErrorHandler::errorT(CEDARFILE__EXIT__GETTING_NEXT,"ssss",CEDARFILE__FATAL__GETTING_NEXT,ENDL,CEDARFILE__MSG__HOW_TO_CONNECT,ENDL);
    }
  return 0;
}

int CedarCrayBlockingFormat::get_first_CedarGroup (CedarGroup &crGroupRecord)
{
  cerr<<"CedarCrayBlockingFormat::get_first_CedarGroup<- Feature not implemented\n";
  return 1;
}

int CedarCrayBlockingFormat::get_next_CedarGroup (CedarGroup &crGroupRecord)
{
  cerr<<"CedarCrayBlockingFormat::get_netx_CedarGroup<- Feature not implemented\n";
  return 1;
}

int CedarCrayBlockingFormat::append_CedarBlock (CedarBlock &cdBlock)
{
 cerr<<"CedarCrayBlockingFormat::append_CedarBlock<- Feature not implemented\n";
 return 1;
}

const CedarLogicalRecord* CedarCrayBlockingFormat::get_first_logical_record ()
{
  if(get_first_CedarBlock())
    return cdBlock.get_first_record();
  return 0;
}

const CedarLogicalRecord* CedarCrayBlockingFormat::get_next_logical_record ()
{
  plogrec=cdBlock.get_next_record();
  if (plogrec)
    return plogrec;
  else
    {
      if(get_next_CedarBlock())
	return cdBlock.get_first_record();
      return 0;
    }
  return 0;
}

void CedarCrayBlockingFormat::rewind()
{
  CedarCrayBlockingFormat::disconnect();
}
