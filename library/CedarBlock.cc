/*******************************************************************
 * CLASS CedarBlock - Definition
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
#include "CedarBlock.h"
#include "CedarErrorHandler.h"
#ifdef LOGGING_WITH_CEDARDUMP
#include "CedarDump.h"
#endif

using std::endl ;

CedarBlock::CedarBlock():crData(12288,4096)

{
  value=0;
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper().puthead(CEDARBLOCK__PROTOTYPE__1);
      CedarDump::Dumper()<<CEDARBLOCK__MSG__OBJECT_CONSTRUCTED;
      CedarDump::Dumper().puttail(CEDARBLOCK__PROTOTYPE__1); 
#endif
}

// This destructor is defined only if LOGGING_WITH_CEDARDUMP 

CedarBlock::~CedarBlock()
{
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper().puthead(CEDARBLOCK__PROTOTYPE__2);
      CedarDump::Dumper()<<CEDARBLOCK__MSG__OBJECT_DESTRUCTED;
      CedarDump::Dumper().puttail(CEDARBLOCK__PROTOTYPE__2); 
#endif
}


/*
 * do_block_checksum returns 0 if the integrity of this CedarBlock
 * (CedarBlock=Physical Record)
 * is not assured. Of course lets say (even if is trivial) that it will
 * return 1 if the integrity is OK.
 * field_a is the variable that carries across all the array of bytes the XOR operation
 * of the previous field with the next field. At the end field_a is compared to chek_sum to determine
 * the return value 
*/

int CedarBlock::do_block_checksum()
{
#ifdef LOGGING_WITH_CEDARDUMP
    CedarDump::Dumper().puthead(CEDARBLOCK__PROTOTYPE__3);
#endif
  int number_of_bytes=get_block_length()*2;
  field field_a=build_field(0);
  int how_many=number_of_bytes/2-2;
  //Lets calculate the check sum across all the fields in the array but the last one...
  for (int r=0; r<how_many; r++)
    {
      field field_b=build_field(r*2+2);
      field_a=field_a^field_b;
    }
  //now we calculate the check sum with the last field of this CedarBlock
  int check_sum=build_field(number_of_bytes-2);
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper()<<CEDARBLOCK__MSG__CHECK_SUM<<field_a<<" "<<check_sum<<ENDL;
      if (check_sum!=field_a)
	{
	  CedarDump::Dumper()<<"Record check sum failed!"<<endl;
	  field_a=build_field(0);
	  CedarDump::Dumper()<<field_a<<endl;
	  for (int r=0; r<how_many; r++)
	    {
	      field field_b=build_field(r*2+2);
	      field_a=field_a^field_b;
	      CedarDump::Dumper()<<field_b<<" "<<field_a<<endl;
	    }
	}
      CedarDump::Dumper().puttail(CEDARBLOCK__PROTOTYPE__3);
#endif
  if (check_sum==field_a)
    return 1;
  else 
    return 0;
}

/* 
 * The functions get_data_extended_prologue and get_header_extended_prologue
 * assign the values to the prologue fields beyond the 12th position. As defined in 
 * CedarDataTypes, "prologue" is a data type as a struct that wraps the first
 * twelve fields for the concept of prologue for the logical records. These 12 fields are
 * common for all the inherited classes that are CedarDataRecord, CedarHeaderRecord and
 * CedarCatalogRecord. Only CedarDataRecord and CedarHeaderRecord have extended prologue.
 */

inline void CedarBlock::get_data_extended_prologue()
{
  the_data.LPROL=build_field(crData_marker+24);
  the_data.JPAR=build_field(crData_marker+26);
  the_data.MPAR=build_field(crData_marker+28);
  the_data.NROW=build_field(crData_marker+30);
  if ((the_data.LPROL<0) || (the_data.JPAR<0)  || (the_data.MPAR<0)  || (the_data.NROW<0))
    CedarErrorHandler::errorT(CEDARBLOCK__EXIT__NEGATIVE_PROLOGUE_VALUE,"s",CEDARBLOCK__FATAL__NEGATIVE_PROLOGUE_FIELD);
}

inline void CedarBlock::get_header_extended_prologue()
{
  the_header.LPROL=build_field(crData_marker+24);
  the_header.JPAR=build_field(crData_marker+26);
  the_header.MPAR=build_field(crData_marker+28);
  if ((the_data.LPROL<0) || (the_data.JPAR<0)  || (the_data.MPAR<0)  || (the_data.NROW<0))
    CedarErrorHandler::errorT(CEDARBLOCK__EXIT__NEGATIVE_PROLOGUE_VALUE,"s",CEDARBLOCK__FATAL__NEGATIVE_PROLOGUE_FIELD);
}

/* 
 * The function load_data_record_data loads the internal buffer
 * (called data_record_data)
 * of the member object the_data
 * (of type CedarDataRecord)
 * with its corresponding field values from the internal buffer of this CedarBlock object
 * called (crData).
 * Notice that crData_marker marks the current byte position in crData 
 * of the byte that is being used while loading the buffer data_record_data.
 * It is assumed that the prologue for the data member the_data is already loaded
 * and that assumption is safe because these are private member functions.
 * The total amount of fields is calculated with the LTOT of the record minus its prologue length (LPROL)
 * First the crData_marker must be move foward as many bytes as the the_data.LPROL indicates.
 * (the_data.LPROL is in fields and crData_marker is in bytes, that is why it must be multiply by two)
 * In the for loop as fields are assign (therefore two bytes are consumed)
 * the crData_marker is move foward by two
 * This function will not return anything after it loads the_data object,
 * Leaving the crData_marker in the first byte of the next Logical record
 */

void CedarBlock::load_data_record_data()
{
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper().puthead(CEDARBLOCK__PROTOTYPE__6);
      CedarDump::Dumper()<<CEDARBLOCK__MSG__TOTAL_RECORD_LENGTH_FIELDS<<the_data.prologue.LTOT<<ENDL;
#endif  
  register int total_field_number=the_data.prologue.LTOT-the_data.LPROL;
  crData_marker=crData_marker+(the_data.LPROL*2);
  for (register int i=0; i<total_field_number; i++)
    {
      the_data.data_record_data[i]=build_field(crData_marker);
      crData_marker=crData_marker+2;
    }
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper()<<CEDARBLOCK__MSG__DATAMARKER_POS<<crData_marker<<ENDL;
      CedarDump::Dumper()<<CEDARBLOCK__MSG__BLOCK_LENGTH<<get_block_length()*2<<ENDL;
      CedarDump::Dumper().puttail(CEDARBLOCK__PROTOTYPE__6);
#endif
}

/* 
 * load_catalog_record_data and load_header_record_data are similar in the 
 * way the load the data buffer for the_catalog and the_header objects
 * data members respectively. First they calculate (in bytes) the length
 * of the data section for the record, then in the for loop the bytes are assign 
 * directly and as many as the "total_byte_length". Finally the crData_marker
 * is move foward as many bytes as indicated by the field LTOT 
 */ 

void CedarBlock::load_catalog_record_data()
{
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper().puthead(CEDARBLOCK__PROTOTYPE__4);
      CedarDump::Dumper()<<CEDARBLOCK__MSG__TOTAL_RECORD_LENGTH_BYTES<<(the_catalog.prologue.LTOT*2)<<ENDL;
#endif
  register int total_byte_length=(the_catalog.prologue.LTOT*2)-80;
  for (register int i=0; i<total_byte_length; i++)
    the_catalog.catalog_record_data[i]=crData[i+80+crData_marker];
  crData_marker=crData_marker+(the_catalog.prologue.LTOT*2);
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper()<<CEDARBLOCK__MSG__DATAMARKER_POS<<crData_marker<<ENDL;
      CedarDump::Dumper()<<CEDARBLOCK__MSG__BLOCK_LENGTH<<get_block_length()*2<<ENDL;
      CedarDump::Dumper().puttail(CEDARBLOCK__PROTOTYPE__4);
#endif

}

void CedarBlock::load_header_record_data()
{
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper().puthead(CEDARBLOCK__PROTOTYPE__5);
      CedarDump::Dumper()<<CEDARBLOCK__MSG__TOTAL_RECORD_LENGTH_BYTES<<(the_header.prologue.LTOT*2)<<ENDL;
#endif  
  register int total_byte_length=(the_header.prologue.LTOT*2)-80;
  for (register int i=0; i<total_byte_length; i++)
    the_header.header_record_data[i]=crData[i+80+crData_marker];
  crData_marker=crData_marker+(the_header.prologue.LTOT*2);
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper()<<CEDARBLOCK__MSG__DATAMARKER_POS<<crData_marker<<ENDL; 
      CedarDump::Dumper()<<CEDARBLOCK__MSG__BLOCK_LENGTH<<get_block_length()*2<<ENDL;
      CedarDump::Dumper().puttail(CEDARBLOCK__PROTOTYPE__5);
#endif
}

/* 
 * build_record_prologue takes a kind_record value (1=data, 2=catalog, 3=header)
 * and loads the "prologue data member" (inherited from CedarLogicalRecord)
 * for either the_data or the_header or the_catalog.
 * This prologue represents the common first 12 fields for the prologue
 * across any kind of Logical Record 
 */

void CedarBlock::build_record_prologue(int kind_record)
{
  CedarLogicalRecord *lr=0;
  switch (kind_record)
    {
    case 1:
      lr=&the_data;
      break;
    case 2:
      lr=&the_catalog;
      break;
    case 3:
      lr=&the_header;
    }
  
  lr->prologue.LTOT=   build_field(crData_marker);
  lr->prologue.KREC=   build_field(crData_marker+2);
  lr->prologue.KINST=  build_field(crData_marker+4);
  lr->prologue.KINDAT= build_field(crData_marker+6);

#ifdef CEDAR_CHECK_VALID_DATES  
  /*
   * I???? prologue members must be treated different since we must check that the
   * value returned by build_field is a valid date_field value
   */
  CedarDate my_date;
  field year_field, date_field, hour_minute_field, centisecond_field;    

  year_field=build_field(crData_marker+8);
  date_field=build_field(crData_marker+10);
  hour_minute_field=build_field(crData_marker+12);
  centisecond_field=build_field(crData_marker+14);

  /*
   * When calling CedarDate::validate_fields the four parameters are date_fields and those are positive,
   * year_field, date_field, hour_minute_field and centisecond_field are field type so they can be negative. 
   * We must avoid that the casting process upon using CedarDate::validate_fields corrupts the data so first
   * we get sure they are not negative.
   */
  if ( (year_field<0) || (date_field<0) || (hour_minute_field<0) || (centisecond_field<0) )
    {
      CedarErrorHandler::errorT(CEDARBLOCK__EXIT__DATE_FIELD_NEGATIVE,"ssisisisisis",CEDARBLOCK__FATAL__DATE_VALUE_NEGATIVE,CEDARBLOCK__FATAL__DATE_VALUES_ARE,kind_record," ",year_field," ",date_field," ",hour_minute_field," ",centisecond_field,ENDL);
    }
  else if (!(my_date.validate_fields(year_field, date_field, hour_minute_field, centisecond_field)))
    {
      CedarErrorHandler::errorT(CEDARBLOCK__EXIT__INVALID_DATE,"ssisisisisis",CEDARBLOCK__FATAL__INVALID_DATE,CEDARBLOCK__FATAL__DATE_VALUES_ARE,kind_record," ",year_field," ",date_field," ",hour_minute_field," ",centisecond_field,ENDL);
    }

  lr->prologue.IBYRT= year_field; 
  lr->prologue.IBDTT= date_field;
  lr->prologue.IBHMT= hour_minute_field;
  lr->prologue.IBCST= centisecond_field; 
  
  year_field=build_field(crData_marker+16);
  date_field=build_field(crData_marker+18);
  hour_minute_field=build_field(crData_marker+20);
  centisecond_field=build_field(crData_marker+22);

  if ( (year_field<0) || (date_field<0) || (hour_minute_field<0) || (centisecond_field<0) )
    {
      CedarErrorHandler::errorT(CEDARBLOCK__EXIT__DATE_FIELD_NEGATIVE,"ssisisisisis",CEDARBLOCK__FATAL__DATE_VALUE_NEGATIVE,CEDARBLOCK__FATAL__DATE_VALUES_ARE,kind_record," ",year_field," ",date_field," ",hour_minute_field," ",centisecond_field,ENDL);
    }
  else if (!(my_date.validate_fields(year_field, date_field, hour_minute_field, centisecond_field)))
    {
      CedarErrorHandler::errorT(CEDARBLOCK__EXIT__INVALID_DATE,"ssisisisisis",CEDARBLOCK__FATAL__INVALID_DATE,CEDARBLOCK__FATAL__DATE_VALUES_ARE,kind_record," ",year_field," ",date_field," ",hour_minute_field," ",centisecond_field,ENDL);
    }
  
  lr->prologue.IEYRT= year_field; 
  lr->prologue.IEDTT= date_field;
  lr->prologue.IEHMT= hour_minute_field;
  lr->prologue.IECST= centisecond_field; 

#else

  lr->prologue.IBYRT= build_field(crData_marker+8);
  lr->prologue.IBDTT= build_field(crData_marker+10);
  lr->prologue.IBHMT= build_field(crData_marker+12);
  lr->prologue.IBCST= build_field(crData_marker+14);
  
  lr->prologue.IEYRT= build_field(crData_marker+16);
  lr->prologue.IEDTT= build_field(crData_marker+18);
  lr->prologue.IEHMT= build_field(crData_marker+20);
  lr->prologue.IECST= build_field(crData_marker+22);
    
#endif
}

/* 
 * get_first_record and get_next_record try to be really simple in their design.
 * By calling other private member fuctions in THE RIGHT ORDER 
 * (that is first loading the prologue, then the extended prologue 
 * if applicable and finally the data buffer)
 * the records are built from the bytes loaded in the internal
 * buffer of this CedarBlock (crData).
 * To achieve a run time polymorphism  the right data member
 * (the_data or the_header or the_catalog)
 * for the case indicated in "kind_of_record" is returned as a
 * pointer to parent class "CedarLogicalRecord*"
 * If the calcualted "kind_of_record" is not a valid value (1002, 2001, 3002)
 * NULL is returned 
 */

const CedarLogicalRecord* CedarBlock::get_first_record()
{
  crData_marker=2;
  int kind_of_record=build_field(crData_marker+2);
  switch (kind_of_record)
    {
    case 1002:
      build_record_prologue(1);
      get_data_extended_prologue();
      load_data_record_data();
      return &the_data;
      break;
    case 2001:
      build_record_prologue(2);
      load_catalog_record_data();
      return &the_catalog;
      break;
    case 3002:
      build_record_prologue(3);
      get_header_extended_prologue();     
      load_header_record_data();
      return &the_header;
      break;
    default:
#ifdef LOGGING_WITH_CEDARDUMP
      CedarDump::Dumper().puthead(CEDARBLOCK__PROTOTYPE__7);
      CedarDump::Dumper()<<CEDARBLOCK__MSG__KIND_OF_RECORD<<kind_of_record<<ENDL;
      CedarDump::Dumper()<<CEDARBLOCK__MSG__KIND_OF_RECORD_NOT_VALID;
      CedarDump::Dumper().puttail(CEDARBLOCK__PROTOTYPE__7);
#endif
      return NULL;
    }
}

const CedarLogicalRecord* CedarBlock::get_next_record()
{
  int total_block_size_without_the_check_sum = (get_block_length()*2)-2;
  if (crData_marker<total_block_size_without_the_check_sum)
    {
      int kind_of_record=build_field(crData_marker+2);
      switch (kind_of_record)
	{
	case 1002:
	  build_record_prologue(1);
	  get_data_extended_prologue();
	  load_data_record_data();
	  return &the_data;
	  break;
	case 2001:
	  build_record_prologue(2);
	  load_catalog_record_data();
	  return &the_catalog;
	  break;
	case 3002:
	  build_record_prologue(3);
	  get_header_extended_prologue();     
	  load_header_record_data();
	  return &the_header;
	  break;
	default:
#ifdef LOGGING_WITH_CEDARDUMP
	  CedarDump::Dumper().puthead(CEDARBLOCK__PROTOTYPE__8);
	  CedarDump::Dumper()<<CEDARBLOCK__MSG__KIND_OF_RECORD<<kind_of_record<<ENDL;
	  CedarDump::Dumper()<<CEDARBLOCK__MSG__KIND_OF_RECORD_NOT_VALID;
	  CedarDump::Dumper().puttail(CEDARBLOCK__PROTOTYPE__8);
#endif
	  return NULL;
	} 
    }
  else 
    return NULL;
}

// flush invokes CedarArray::flush_array to clean the data buffer for this CedarBlock (crData) 

void CedarBlock::flush()
{
  crData.flush_array();
}

