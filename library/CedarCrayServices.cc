/*******************************************************************
 * CLASS CedarCrayServices - Definition
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
#include "CedarCrayServices.h"
#include "CedarErrorHandler.h"
#ifdef LOGGING_WITH_CEDARDUMP
#include "CedarDump.h"
#endif

CedarCrayServices::CedarCrayServices()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARCRAYSERVICES__PROTOTYPE__1);
  CedarDump::Dumper()<<CEDARCRAYSERVICES__MSG__CONSTRUCTED;
  CedarDump::Dumper().puttail(CEDARCRAYSERVICES__PROTOTYPE__1);
#endif
}

CedarCrayServices::~CedarCrayServices()
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARCRAYSERVICES__PROTOTYPE__2);
  CedarDump::Dumper()<<CEDARCRAYSERVICES__MSG__DESTRUCTED;
  CedarDump::Dumper().puttail(CEDARCRAYSERVICES__PROTOTYPE__2);
#endif
}


void CedarCrayServices::load_block_control(control &ctrl, word my_word)
{
  ctrl.block_control.M=((8*my_word.b0)+(4*my_word.b1)+(2*my_word.b2)+(1*my_word.b3));
  ctrl.block_control.BDF=my_word.b11;
  ctrl.block_control.BN=  ( (8388608*my_word.b31)+(4194304*my_word.b32)+(2097152*my_word.b33)+(1048576*my_word.b34)+ \
                            (524288 *my_word.b35)+(262144 *my_word.b36)+(131072 *my_word.b37)+(65536  *my_word.b38)+ \
                            (32768  *my_word.b39)+(16384  *my_word.b40)+(8192   *my_word.b41)+(4096   *my_word.b42)+ \
		            (2048   *my_word.b43)+(1024   *my_word.b44)+(512    *my_word.b45)+(256    *my_word.b46)+ \
		            (128    *my_word.b47)+(64     *my_word.b48)+(32     *my_word.b49)+(16     *my_word.b50)+ \
		            (8      *my_word.b51)+(4      *my_word.b52)+(2      *my_word.b53)+(1      *my_word.b54)  \
		          );
  ctrl.block_control.FWI= (
			    (256*my_word.b55)+(128*my_word.b56)+(64*my_word.b57)+(32*my_word.b58)+(16*my_word.b59)+  \
			    (8  *my_word.b60)+(4  *my_word.b61)+(2 *my_word.b62)+(1 *my_word.b63)                    \
			  );
  ctrl.forward=ctrl.block_control.FWI;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARCRAYSERVICES__PROTOTYPE__3);
  show_word(my_word);
  CedarDump::Dumper()<<CEDARCRAYSERVICES__MSG__CONTROL_TYPE<<ctrl.type_of_control<<endl;
  CedarDump::Dumper()<<CEDARCRAYSERVICES__MSG__FORWARD_INDEX<<ctrl.forward<<endl;
  CedarDump::Dumper()<<"M= "<<ctrl.block_control.M<<endl;
  CedarDump::Dumper()<<"BDF= "<<ctrl.block_control.BDF<<endl;
  CedarDump::Dumper()<<"BN= "<<ctrl.block_control.BN<<endl;
  CedarDump::Dumper()<<"FWI= "<<ctrl.block_control.FWI<<endl;
  CedarDump::Dumper().puttail(CEDARCRAYSERVICES__PROTOTYPE__3);
#endif
}

void CedarCrayServices::load_record_control(control &ctrl, word my_word)
{
  ctrl.record_control.M=((8*my_word.b0)+(4*my_word.b1)+(2*my_word.b2)+(1*my_word.b3));
  ctrl.record_control.UBC=((32*my_word.b4)+(16*my_word.b5)+(8*my_word.b6)+(4*my_word.b7)+(2*my_word.b8)+(1*my_word.b9));
  ctrl.record_control.TRAN=my_word.b10;
  ctrl.record_control.BDF=my_word.b11;
  ctrl.record_control.SRS=my_word.b12;
  ctrl.record_control.PFI=( (524288 *my_word.b20)+(262144 *my_word.b21)+(131072 *my_word.b22)+(65536  *my_word.b23)+ \
                            (32768  *my_word.b24)+(16384  *my_word.b25)+(8192   *my_word.b26)+(4096   *my_word.b27)+ \
		            (2048   *my_word.b28)+(1024   *my_word.b29)+(512    *my_word.b30)+(256    *my_word.b31)+ \
		            (128    *my_word.b32)+(64     *my_word.b33)+(32     *my_word.b34)+(16     *my_word.b35)+ \
		            (8      *my_word.b36)+(4      *my_word.b37)+(2      *my_word.b38)+(1      *my_word.b39)  \
			  );
  ctrl.record_control.PRI=( (16384*my_word.b40)+(8192*my_word.b41)+(4096*my_word.b42)+(2048*my_word.b43)+(1024*my_word.b44)+ \
			    (512  *my_word.b45)+(256 *my_word.b46)+(128 *my_word.b47)+(64  *my_word.b48)+(32  *my_word.b49)+ \
			    (16   *my_word.b50)+(8   *my_word.b51)+(4   *my_word.b52)+(2   *my_word.b53)+(1   *my_word.b54)  \
			  );
  ctrl.record_control.FWI=(
			    (256*my_word.b55)+(128*my_word.b56)+(64*my_word.b57)+(32*my_word.b58)+(16*my_word.b59)+  \
			    (8  *my_word.b60)+(4  *my_word.b61)+(2 *my_word.b62)+(1 *my_word.b63)                    \
			  );
  ctrl.forward=ctrl.record_control.FWI;
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper().puthead(CEDARCRAYSERVICES__PROTOTYPE__4);
  show_word(my_word);
  CedarDump::Dumper()<<CEDARCRAYSERVICES__MSG__CONTROL_TYPE<<ctrl.type_of_control<<endl;
  CedarDump::Dumper()<<CEDARCRAYSERVICES__MSG__FORWARD_INDEX<<ctrl.forward<<endl;
  CedarDump::Dumper()<<"M= "<<ctrl.record_control.M<<endl;
  CedarDump::Dumper()<<"UBC= "<<ctrl.record_control.UBC<<endl;
  CedarDump::Dumper()<<"TRAN= "<<ctrl.record_control.TRAN<<endl;
  CedarDump::Dumper()<<"BDF= "<<ctrl.record_control.BDF<<endl;
  CedarDump::Dumper()<<"SRS= "<<ctrl.record_control.SRS<<endl;
  CedarDump::Dumper()<<"PFI= "<<ctrl.record_control.PFI<<endl;
  CedarDump::Dumper()<<"PRI= "<<ctrl.record_control.PRI<<endl;
  CedarDump::Dumper()<<"FWI="<<ctrl.record_control.FWI<<endl;
  CedarDump::Dumper().puttail(CEDARCRAYSERVICES__PROTOTYPE__4);
#endif
}

int CedarCrayServices::calculate_M_on_word(word my_word)
{
  int val=((8*my_word.b0)+(4*my_word.b1)+(2*my_word.b2)+(1*my_word.b3));
  return val;
}


int CedarCrayServices::get_bit (byte val, int pos)
{ 
  int result;
  if ((pos>7)||(pos<0)) 
    {
      CedarErrorHandler::errorT(CEDARCRAYSERVICES__EXIT__ACCESING_WRONG_BIT,"s",CEDARCRAYSERVICES__FATAL__ACCESING_WRONG_BIT);
    }
  switch (pos){
  case 0 :
    result=(val&1);
    if (result==0) return 0;
    else {
      if (result==1) return 1;
    }
    break;
  case 1:
    result=(val&2);
    if (result==0) return 0;
    else {
      if (result==2) return 1;
    }
    break;
  case 2:
    result=(val&4);
    if (result==0) return 0;
    else {
      if (result==4) return 1;
    }
    break;
  case 3:
    result=(val&8);
    if (result==0) return 0;
    else {
      if (result==8) return 1;
    }
    break;
  case 4:
    result=(val&16);
    if (result==0) return 0;
    else {
      if (result==16) return 1;
    }
    break;
  case 5:
    result=(val&32);
    if (result==0) return 0;
    else {
      if (result==32) return 1;
    }
    break;
  case 6:
    result=(val&64);
    if (result==0) return 0;
    else {
      if (result==64) return 1;
    }
    break;
  case 7:
    result=(val&128);
    if (result==0) return 0;
    else {
      if (result==128) return 1;
    }
    break;
  }
  return 0;
}

void CedarCrayServices::show_word(word my_word)
{
#ifdef LOGGING_WITH_CEDARDUMP
  CedarDump::Dumper()<<CEDARCRAYSERVICES__MSG__CURRENT_VALUE_MY_WORD;
  CedarDump::Dumper()<<my_word.b0 ;  CedarDump::Dumper()<<my_word.b1 ;  CedarDump::Dumper()<<my_word.b2 ;  CedarDump::Dumper()<<my_word.b3 ;  
  CedarDump::Dumper()<<my_word.b4 ;  CedarDump::Dumper()<<my_word.b5 ;  CedarDump::Dumper()<<my_word.b6 ;  CedarDump::Dumper()<<my_word.b7 ;
  CedarDump::Dumper()<<my_word.b8 ;  CedarDump::Dumper()<<my_word.b9 ;  CedarDump::Dumper()<<my_word.b10;  CedarDump::Dumper()<<my_word.b11; 
  CedarDump::Dumper()<<my_word.b12;  CedarDump::Dumper()<<my_word.b13;  CedarDump::Dumper()<<my_word.b14;  CedarDump::Dumper()<<my_word.b15;
  CedarDump::Dumper()<<my_word.b16;  CedarDump::Dumper()<<my_word.b17;  CedarDump::Dumper()<<my_word.b18;  CedarDump::Dumper()<<my_word.b19; 
  CedarDump::Dumper()<<my_word.b20;  CedarDump::Dumper()<<my_word.b21;  CedarDump::Dumper()<<my_word.b22;  CedarDump::Dumper()<<my_word.b23;
  CedarDump::Dumper()<<my_word.b24;  CedarDump::Dumper()<<my_word.b25;  CedarDump::Dumper()<<my_word.b26;  CedarDump::Dumper()<<my_word.b27;  
  CedarDump::Dumper()<<my_word.b28;  CedarDump::Dumper()<<my_word.b29;  CedarDump::Dumper()<<my_word.b30;  CedarDump::Dumper()<<my_word.b31;
  CedarDump::Dumper()<<my_word.b32;  CedarDump::Dumper()<<my_word.b33;  CedarDump::Dumper()<<my_word.b34;  CedarDump::Dumper()<<my_word.b35; 
  CedarDump::Dumper()<<my_word.b36;  CedarDump::Dumper()<<my_word.b37;  CedarDump::Dumper()<<my_word.b38;  CedarDump::Dumper()<<my_word.b39;
  CedarDump::Dumper()<<my_word.b40;  CedarDump::Dumper()<<my_word.b41;  CedarDump::Dumper()<<my_word.b42;  CedarDump::Dumper()<<my_word.b43; 
  CedarDump::Dumper()<<my_word.b44;  CedarDump::Dumper()<<my_word.b45;  CedarDump::Dumper()<<my_word.b46;  CedarDump::Dumper()<<my_word.b47;
  CedarDump::Dumper()<<my_word.b48;  CedarDump::Dumper()<<my_word.b49;  CedarDump::Dumper()<<my_word.b50;  CedarDump::Dumper()<<my_word.b51;  
  CedarDump::Dumper()<<my_word.b52;  CedarDump::Dumper()<<my_word.b53;  CedarDump::Dumper()<<my_word.b54;  CedarDump::Dumper()<<my_word.b55;
  CedarDump::Dumper()<<my_word.b56;  CedarDump::Dumper()<<my_word.b57;  CedarDump::Dumper()<<my_word.b58;  CedarDump::Dumper()<<my_word.b59; 
  CedarDump::Dumper()<<my_word.b60;  CedarDump::Dumper()<<my_word.b61;  CedarDump::Dumper()<<my_word.b62;  CedarDump::Dumper()<<my_word.b63;
  CedarDump::Dumper()<<endl;
#endif
}

