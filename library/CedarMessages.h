/*******************************************************************
 * CEDAR API - Messages
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

#ifndef CedarMessages_h_
#define CedarMessages_h_ 1

/*
  Syntax for CEDAR API Messages:
  "CLASSNAME" + "TYPE OF MESSAGE" + "MESSAGE NAME"
  
  where:
  
  "CLASSNAME"         identifies the class that is using the message.
  "TYPE OF MESSAGE"   can be "MSG" for simple messages, "FATAL" for fatal 
  messages when errors occur or a "PROTOTYPE" to create
  a message that indicates the prototype for a class member function.
  "MESSAGE NAME"      Any name you may wish for your message.
  
  "CLASSNAME" and  "TYPE OF MESSAGE" and "MESSAGE NAME" are linked by duble under score ( __ ).
  "MESSAGE NAME" words are linked with single under score ( _ ).
*/


// MESSAGES FOR THE CLASS CedarDump.

#define CEDARDUMP__PROTOTYPE__1                 			"CedarDump::CedarDump()\n"
#define CEDARDUMP__PROTOTYPE__2                 			"CedarDump::CedarDump(char *)\n"
#define CEDARDUMP__PROTOTYPE__3                 			"CedarDump::~CedarDump()\n"
#define CEDARDUMP__FATAL__OPENING_FILE_BUFFER 				"Cedar: Fatal; ofstream object for dumper can not be created.\n"
#define CEDARDUMP__MSG__CONSTRUCTING            			"Message: CedarDump object for debugging program constructed\n"
#define CEDARDUMP__MSG__DESTRUCTING             			"Message: destructing CedarDump object\n"
#define CEDARDUMP__MSG__LOG_HEADER             				"Opening log file, the current time zone, date and time are:\n"
#define CEDARDUMP__MSG__LOG_TAIL               				"Closing log file, the current time zone, date and time are:\n"
#define CEDARDUMP__MSG__HEADER_MESSAGE         				"BEGIN DUMPING FROM "
#define CEDARDUMP__MSG__TAIL_MESSAGE          				"END DUMPING FROM "
#define CEDARDUMP__MSG__PROCESS_ID            			 	"The current process id is "
#define CEDARDUMP__MSG__CURRENT_TIME					"Current time is-> "

// MESSAGES FOR THE TEMPLATE CedarArray.

#define CEDARARRAY__PROTOTYPE__1					"CedarArray<TYPE>::CedarArray(int, int)\n"
#define CEDARARRAY__PROTOTYPE__2					"CedarArray<TYPE>::~CedarArray()\n"
#define CEDARARRAY__PROTOTYPE__3					"void CedarArray<TYPE>::CedarArray(const CedarArray<TYPE> &)\n"
#define CEDARARRAY__PROTOTYPE__4					"void CedarArray<TYPE>::attach_debug(CedarDump *)\n"
#define CEDARARRAY__PROTOTYPE__5					"void CedarArray<TYPE>::deattach_debug()\n"
#define CEDARARRAY__PROTOTYPE__6					"void CedarArray<TYPE>::flush_array()\n"
#define CEDARARRAY__PROTOTYPE__7					"TYPE &CedarArray <TYPE>::operator[](int)\n"
#define CEDARARRAY__PROTOTYPE__8					"CedarArray<TYPE> & CedarArray<TYPE>::operator=(const CedarArray <TYPE> &)\n"
#define CEDARARRAY__PROTOTYPE__9					"int CedarArray<TYPE>::set_size(int)\n"
#define CEDARARRAY__PROTOTYPE__10					"void CedarArray<TYPE>::set_delta(int)\n"
#define CEDARARRAY__FATAL__WRONG_SIZE_OR_DELTA				"Cedar: Fatal; attempting to create an array with SIZE smaller than ONE or DELTA smaller than ZERO.\n"
#define CEDARARRAY__FATAL__DELTA_CAN_NOT_BE_SMALLER_THAN_ZERO		"Cedar: Fatal; attempting to set DELTA smaller than ZERO.\n"
#define CEDARARRAY__FATAL__ALLOCATION_ERROR_FOR_BUFFER_P		"Cedar: Fatal; invalid memory handler or allocation error for formal array.\n"
#define CEDARARRAY__FATAL__EXCEPTION_REPORTED_OPERATOR_NEW		"Cedar: Fatal; An exception was throwed by operator new when attempting to allocate memory.\n"
#define CEDARARRAY__FATAL__ALLOCATION_ERROR_FOR_BUFFER_TEMP		"Cedar: Fatal; invalid memory handler or allocation error for temp array.\n"
#define CEDARARRAY__FATAL__CAN_NOT_GROW_ARRAY_WITH_DELTA_ZERO		"Cedar: Fatal; attempting to grow array size when DELTA is ZERO.\n"
#define CEDARARRAY__FATAL__CAN_NOT_ACCESS_NEGATIVE_INDEX		"Cedar: Fatal; attempting to access an index for the array smaller than ZERO.\n"
#define CEDARARRAY__FATAL__CAN_NOT_SET_ARRAY_SIZE_SMALLER_THAN_ONE	"Cedar: Fatal; attempting to set the SIZE for the array smaller than ONE.\n"
#define CEDARARRAY__MSG__DESTRUCTING_ARRAY				"Message: starting destruction of CEDARarray object\n"
#define CEDARARRAY__MSG__ARRAY_FLUSHED					"Message: array has been flushed\n"
#define CEDARARRAY__MSG__OUT_OF_BOUNDARIES				"Message: array out of boundaries on const object, trying to access index in size -> "
#define CEDARARRAY__MSG__CALLING_SET_SIZE				"Message: calling function set_size to grow array\n"
#define CEDARARRAY__MSG__ARRAY_SIZE					"Message: array size is changing from size to new_size->: "
#define CEDARARRAY__MSG__SET_SIZE_SUCCEED				"Message: set_size succeed\n"
#define CEDARARRAY__MSG__ATTACH_TO_CEDARDUMP				"Message: array is being attached to CEDARdump object now\n"
#define CEDARARRAY__MSG__DEATTACH_TO_CEDARDUMP				"Message: array is being deattached from CEDARdump object now\n"
#define CEDARARRAY__MSG__FLUSHING_ARRAY					"Message: Attempting to flush array and reallocate memory\n"
#define CEDARARRAY__MSG__CALLING_OVERLOADED_EQUAL			"Message: calling overloaded operator =\n"
#define CEDARARRAY__MSG__DEBUGGING_INHERITED				"Message: Debugging property inherited\n"
#define CEDARARRAY__MSG__ARRAY_CONSTRUCTED				"Message: Object CedarArray constructed\n"
#define CEDARARRAY__MSG__NEW_OBJECT_SIZE				"Message: New CedarArray size "
#define CEDARARRAY__MSG__NEW_OBJECT_DELTA				"Message: New CedarArray delta "
#define CEDARARRAY__MSG__AMOUNT_OF_MEMORY_IN_USE			"Message: Number of bytes used by this CedarArray Object-> "

// MESSAGES FOR THE CLASS CedarBlock

#define CEDARBLOCK__PROTOTYPE__1 					"CedarBlock::CedarBlock()\n"
#define CEDARBLOCK__PROTOTYPE__2 					"CedarBlock::~CedarBlock()\n"
#define CEDARBLOCK__PROTOTYPE__3 					"int CedarBlock::do_block_checksum()\n"
#define CEDARBLOCK__PROTOTYPE__4 					"void CedarBlock::load_catalog_record_data()\n"
#define CEDARBLOCK__PROTOTYPE__5 					"void CedarBlock::load_header_record_data()\n"
#define CEDARBLOCK__PROTOTYPE__6 					"void CedarBlock::load_data_record_data()\n"
#define CEDARBLOCK__PROTOTYPE__7 					"CedarLogicalRecord* CedarBlock::get_first_record()\n"
#define CEDARBLOCK__PROTOTYPE__8 					"CedarBlock::get_next_record()\n"
#define CEDARBLOCK__FATAL__DATE_VALUE_NEGATIVE				"Cedar: Fatal; detected a date value negative when loading data from cbf file.\n"
#define CEDARBLOCK__FATAL__INVALID_DATE					"Cedar: Fatal; an invalid date has been detected when loading data from cbf file.\n"
#define CEDARBLOCK__FATAL__DATE_VALUES_ARE				"Cedar: Fatal; Current type of record, year, date, time and centisecond values are-> "
#define CEDARBLOCK__FATAL__NEGATIVE_PROLOGUE_FIELD			"Cedar: Fatal; either LPROL, JPAR, MPAR or NROWS in this prologue is negative.\n" 
#define CEDARBLOCK__MSG__OBJECT_CONSTRUCTED           			"CedarBlock constructed\n"
#define CEDARBLOCK__MSG__OBJECT_DESTRUCTED            			"CedarBlock destructed\n"
#define CEDARBLOCK__MSG__CHECK_SUM                    			"check sum values "
#define CEDARBLOCK__MSG__TOTAL_RECORD_LENGTH_BYTES    			"Total length of record (bytes)= "
#define CEDARBLOCK__MSG__TOTAL_RECORD_LENGTH_FIELDS   			"Total length of record (fields)= "
#define CEDARBLOCK__MSG__KIND_OF_RECORD               			"kind_of_record= "
#define CEDARBLOCK__MSG__KIND_OF_RECORD_NOT_VALID     			"Message: the previous value does not match any valid number to calculate the kind of logical record. Returning NULL\n"
#define CEDARBLOCK__MSG__DATAMARKER_POS               			"The datamarker indicator inside the crData buffer is in the byte "
#define CEDARBLOCK__MSG__BLOCK_LENGTH                         		"CedarBlock::get_block_length() indicates that the total amount of bytes of data loaded in the crData buffer for this CedarBlock object are "
#define CEDARBLOCK__MSG__VERSION					"CedarBlock was compiled into and object module on "
#define CEDARBLOCK__MSG__LOGGING_WITH_CEDARDUMP				"CedarBlock is LOGGING_WITH_CEDARDUMP\n"
#define CEDARBLOCK__MSG__CEDAR_USE_EXCEPTIONS				"CedarBlock with CEDAR_USE_EXCEPTIONS\n"

// MESSAGES FOR THE CLASS CedarLogicalRecord


#define CEDARLOGICALRECORD__PROTOTYPE__1				"CedarLogicalRecord::CedarLogicalRecord()\n"
#define CEDARLOGICALRECORD__PROTOTYPE__2 				"CedarLogicalRecord::~CedarLogicalRecord()\n"
#define CEDARLOGICALRECORD__PROTOTYPE__3 				"int CedarLogicalRecord::get_record_length()\n"
#define CEDARLOGICALRECORD__PROTOTYPE__4 				"CedarDate CedarLogicalRecord::get_record_begin_date()\n"
#define CEDARLOGICALRECORD__PROTOTYPE__5				"CedarDate CedarLogicalRecord::get_record_end_date()\n"
#define CEDARLOGICALRECORD__PROTOTYPE__6				"int CedarLogicalRecord::validate_record(field , field, CedarDate &, CedarDate &)\n"
#define CEDARLOGICALRECORD___FATAL___DATE_FIELD_NEGATIVE 		"Cedar: Fatal; One of the date_field variables is negative."
#define CEDARLOGICALRECORD__MSG__CONSTRUCTED 				"Constructing object\n"
#define CEDARLOGICALRECORD__MSG__DESTRUCTED 				"Destructing object\n"
#define CEDARLOGICALRECORD__MSG__VERSION				"CedarLogicalRecord was compiled into and object module on "
#define CEDARLOGICALRECORD__MSG__LOGGING_WITH_CEDARDUMP			"CedarLogicalRecord is LOGGING_WITH_CEDARDUMP\n"
#define CEDARLOGICALRECORD__MSG__CEDAR_USE_EXCEPTIONS			"CedarLogicalRecord with CEDAR_USE_EXCEPTIONS\n"


// MESSAGES FOR THE CLASS CedarCatalogRecord

#define CEDARCATALOGRECORD__PROTOTYPE__1	       			"CedarCatalogRecord::CedarCatalogRecord()\n"
#define CEDARCATALOGRECORD__PROTOTYPE__2       				"CedarCatalogRecord::~CedarCatalogRecord()\n"
#define CEDARCATALOGRECORD__PROTOTYPE__3     				"void CedarCatalogRecord::save_data_buffer(ofstream &)\n"
#define CEDARCATALOGRECORD__MSG__CONSTRUCTED				"Constructed catalog record\n"
#define CEDARCATALOGRECORD__MSG__DESTRUCTED      			"Destructing catalog record\n"
#define CEDARCATALOGRECORD__MSG__NUMBER_BYTES_DATA 			"Number of bytes of data for this catalog record= "
#define CEDARCATALOGRECORD__MSG__VERSION				"CedarCatalogRecord was compiled into and object module on "
#define CEDARCATALOGRECORD__MSG__LOGGING_WITH_CEDARDUMP			"CedarCatalogRecord is LOGGING_WITH_CEDARDUMP\n"
#define CEDARCATALOGRECORD__MSG__CEDAR_USE_EXCEPTIONS			"CedarCatalogRecord with CEDAR_USE_EXCEPTIONS\n"

// MESSAGES FOR THE CLASS CedarDataRecord

#define CEDARDATARECORD__PROTOTYPE__1       				"CedarDataRecord::CedarDataRecord()\n"
#define CEDARDATARECORD__PROTOTYPE__2       				"CedarDataRecord::~CedarDataRecord()\n"
#define CEDARDATARECORD__PROTOTYPE__3       				"void CedarDataRecord::save_data_buffer(ofstream &)\n"
#define CEDARDATARECORD__MSG__CONSTRUCTED          			"Constructed data record\n"
#define CEDARDATARECORD__MSG__DESTRUCTED          			"Destructing data record\n"
#define CEDARDATARECORD__MSG__NUMBER_FIELDS_DATA   			"Number of fields of data for this data record= "
#define CEDARDATARECORD__MSG__VERSION					"CedarDataRecord was compiled into and object module on "
#define CEDARDATARECORD__MSG__LOGGING_WITH_CEDARDUMP			"CedarDataRecord is LOGGING_WITH_CEDARDUMP\n"
#define CEDARDATARECORD__MSG__CEDAR_USE_EXCEPTIONS			"CedarDataRecord with CEDAR_USE_EXCEPTIONS\n"

// MESSAGES FOR THE CLASS CedarHeaderRecord

#define CEDARHEADERRECORD__PROTOTYPE__1      				"CedarHeaderRecord::CedarHeaderRecord()\n"
#define CEDARHEADERRECORD__PROTOTYPE__2       				"CedarHeaderRecord::~CedarHeaderRecord()\n"
#define CEDARHEADERRECORD__PROTOTYPE__3       				"void CedarHeaderRecord::save_data_buffer(ofstream &)\n"
#define CEDARHEADERRECORD__MSG__CONSTRUCTED       			"Constructed header record\n"
#define CEDARHEADERRECORD__MSG__DESTRUCTED       			"Destructing header record\n"
#define CEDARHEADERRECORD__MSG__NUMBER_BYTES_DATA 			"Number of bytes of data for this header record= "
#define CEDARHEADERRECORD__MSG__VERSION					"CedarHeaderRecord was compiled into and object module on "
#define CEDARHEADERRECORD__MSG__LOGGING_WITH_CEDARDUMP			"CedarHeaderRecord is LOGGING_WITH_CEDARDUMP\n"
#define CEDARHEADERRECORD__MSG__CEDAR_USE_EXCEPTIONS			"CedarHeaderRecord with CEDAR_USE_EXCEPTIONS\n"

// MESSAGES FOR THE CLASS CedarCrayServices
	
#define CEDARCRAYSERVICES__PROTOTYPE__1					"CedarCrayServices::CedarCrayServices()\n"
#define CEDARCRAYSERVICES__PROTOTYPE__2 				"CedarCrayServices::~CedarCrayServices()\n"
#define CEDARCRAYSERVICES__PROTOTYPE__3 				"void CedarCrayServices::load_block_control(control &, word )\n"
#define CEDARCRAYSERVICES__PROTOTYPE__4 				"void CedarCrayServices::load_record_control(control &, word )\n"
#define CEDARCRAYSERVICES__FATAL__ACCESING_WRONG_BIT			"Cedar: Fatal; attempting to access a bit number above 7 or below 0 when valid range is [0,7].\n"
#define CEDARCRAYSERVICES__MSG__CONSTRUCTED 				"Message: Object constructed\n"
#define CEDARCRAYSERVICES__MSG__DESTRUCTED 				"Message: Object Destructed\n"
#define CEDARCRAYSERVICES__MSG__CONTROL_TYPE				"This Control is type "
#define CEDARCRAYSERVICES__MSG__FORWARD_INDEX				"The forward index is "
#define CEDARCRAYSERVICES__MSG__CURRENT_VALUE_MY_WORD			"Current Value for my_word use to load control\n"
#define CEDARCRAYSERVICES__MSG__VERSION					"CedarCrayServices was compiled into and object module on "
#define CEDARCRAYSERVICES__MSG__LOGGING_WITH_CEDARDUMP			"CedarCrayServices is LOGGING_WITH_CEDARDUMP\n"
#define CEDARCRAYSERVICES__MSG__CEDAR_USE_EXCEPTIONS			"CedarCrayServices with CEDAR_USE_EXCEPTIONS\n"

// MESSAGES FOR THE CLASS CedarFile

#define CEDARFILE__PROTOTYPE__1 						"Cedarfile::Cedarfile()\n"
#define CEDARFILE__PROTOTYPE__2 						"Cedarfile::~Cedarfile()\n"
#define CEDARFILE__PROTOTYPE__3 						"int Cedarfile::connect()\n"
#define CEDARFILE__PROTOTYPE__4 						"void CedarFile::use_cbf_file(char*)\n"
#define CEDARFILE__PROTOTYPE__5 						"void CedarFile::get_cosBlock()\n"
#define CEDARFILE__PROTOTYPE__6 						"int CedarFile::get_first_CedarBlock(CedarBlock &)\n"
#define CEDARFILE__PROTOTYPE__7 						"int CedarFile::get_next_CedarBlock(CedarBlock &)\n"
#define CEDARFILE__PROTOTYPE__8							"void CedarFile::load_my_control()\n"
#define CEDARFILE__PROTOTYPE__9							"int CedarFile::get_cache_optimal_size()\n"
#define CEDARFILE__PROTOTYPE__10						"int CedarFile::disconnect()\n"
#define CEDARFILE__FATAL__GETTING_NEXT    					"Cedar: Fatal; CedarFile Object confused with status of sequencial access.\n"
#define CEDARFILE__FATAL__FILENAME_NULL       					"Cedar: Fatal; Passing NULL as a file name.\n"
#define CEDARFILE__FATAL__FILE_NOT_OPEN                                         "Cedar: Fatal; Cedar File is not open, can not perform operation.\n"
#define CEDARFILE__FATAL__FILE_NAME_TOO_LONG          				"Cedar: Fatal; The file name is longer than 255 characters, CedarFile can not connect.\n"
#define CEDARFILE__FATAL__TYPE_OF_CONTROL 					"Cedar: Fatal; The current word does not match any type of control\n"
#define CEDARFILE__FATAL__INVALID_FORWARD_INDEX					"Cedar: Fatal; The forward index for the current control is invalid, its current value is "
#define CEDARFILE__FATAL__BAD_CHECK_SUM                                         "Cedar: Fatal; Invalid check sum\n"
#define CEDARFILE__FATAL__MUST_BE_END_OF_DATASET                                "Cedar: Fatal; while loading imcomplete COS block at the end of the file, the cray control word is not End Of Dataset (EOD)\n"
#define CEDARFILE__FATAL__NOT_SUPPORTED_CACHE					"Integer size in this machine is too small, minimum size required is 4 bytes"
#define CEDARFILE__FATAL__CAN_NOT_GET_FILE_STAT					"Can not load file info"
#define CEDARFILE__FATAL__CAN_NOT_CREATE_READ_AHEAD_THREAD			"Cedar: Fatal; Can not create thread for read ahead."
#define CEDARFILE__FATAL__UNKNOWN_FORMAT                                        "Cedar: Fatal; The specified format is unknown"
#define CEDARFILE__MSG__COULD_NOT_CONNECT          				"Failed to establish connection to  file -> "
#define CEDARFILE__MSG__COULD_CONNECT              				"Succeed to establish connection to  file -> "
#define CEDARFILE__MSG__DESTRUCTING_OBJECT         				"Destructing cedar_file object\n"
#define CEDARFILE__MSG__OBJECT_CONSTRUCTED         				"The object CedarFile has been construted with debug on\n"
#define CEDARFILE__MSG__GIVING_NAME	           				"Attempting to relate object CedarFile to a CBF file\n"
#define CEDARFILE__MSG__HOW_TO_CONNECT             				"Hint: May be you are calling get_next_logical_record without using first get_first_logical_record. After the object has been related to a file with an open file call, you must start reading data with get_first_logical_record\n"
#define CEDARFILE__MSG__GETTING_BLOCK              				"Getting block number "
#define CEDARFILE__MSG__NUMBER_BYTES               				"Number of bytes read "
#define CEDARFILE__MSG__STATUS_READ_OS             				"The status of os is "
#define CEDARFILE__MSG__EOF_FOUND                  				"Found end of file control word\n"
#define CEDARFILE__MSG__CHANGING_NAME              				"Changing name when object is connected. Disconnecting from file "
#define CEDARFILE__MSG__BAD_BIT_TRUE               				"The bad bit for this ifstream is TRUE\n"
#define CEDARFILE__MSG__EOF_BIT_TRUE               				"The eof bit for this ifstream is TRUE\n"
#define CEDARFILE__MSG__FAIL_BIT_TRUE              				"The fail bit for this ifstream is TRUE\n"
#define CEDARFILE__MSG__GOOD_BIT_TRUE              				"The good bit for this ifstream is TRUE\n"
#define CEDARFILE__MSG__BLOCK_BUFFER_IS            				"The size of the block buffer is "
#define CEDARFILE__MSG__RECORD_SIZE_IS             				"The amount of bytes loaded into block are "
#define CEDARFILE__MSG__THIS_FUNCTION_RETURN       				"This function will return "
#define CEDARFILE__MSG__RECORD_NUMBER_IS           				"This is record "
#define CEDARFILE__MSG__DATASET_FLAG               				"The end of dataset flag is "
#define CEDARFILE__MSG__BYTE_UNIT                  				" bytes"
#define CEDARFILE__MSG__CAN_NOT_CONNECT_OBJECT_IS_NOT_RELATED_TO_CBF_FILE	"Message: can not connect because the object is not related to any CBF file. Use void CedarFile::use_cbf_file(char*) to related this object.\n"    
#define CEDARFILE__MSG__BLOCK_COUNTER_IN_POSITION				"The block counter is now: "
#define CEDARFILE__MSG__VERSION							"CedarFile was compiled into and object module on "
#define CEDARFILE__MSG__LOGGING_WITH_CEDARDUMP					"CedarFile is LOGGING_WITH_CEDARDUMP\n"
#define CEDARFILE__MSG__CEDAR_USE_EXCEPTIONS					"CedarFile with CEDAR_USE_EXCEPTIONS\n"
#define CEDARFILE__MSG__WAIT_THREAD1						"This object waited for the read thread "
#define CEDARFILE__MSG__WAIT_THREAD2						" times"
#define CEDARFILE__MSG__READ_THREAD						"Thread for read ahead initialized"
#define CEDARFILE__MSG__READ_THREAD_EXITING					"Read thread is exiting due to destructor request"
#define CEDARFILE__MSG__NUMBER_COS_BLOCKS1					"This file contains "
#define CEDARFILE__MSG__NUMBER_COS_BLOCKS2					" cosBlock(s)."
#define CEDARFILE__MSG__SIGWORDS_LESS_THAN_0 "Total number of significant words in the physical record smaller than 0"
#define CEDARFILE__MSG__FIRSTWORD_FIRSTLR_LT_0 "First word of the first logical record start smaller than 0"
#define CEDARFILE__MSG__FIRSTWORD_LASTLR_LT_0 "First word of the last logical record start smaller than 0"
#define CEDARFILE__MSG__FIRSTWORD_FIRSTLR_SET_0 "First word of the first logical record start set to 0"
#define CEDARFILE__MSG__LENGTH_FIRSTLR_LT_0 "Length of the first logical record smaller than 0"

// MESSAGES FOR THE CLASS CedarGroup

// MESSAGES FOR THE CLASS CedarStringConversions

#define CEDARSTRINGCONVERSIONS__MSG__VERSION					"CedarStringConversions was compiled into and object module on "
#define CEDARSTRINGCONVERSIONS__MSG__LOGGING_WITH_CEDARDUMP			"CedarStringConversions is LOGGING_WITH_CEDARDUMP\n"
#define CEDARSTRINGCONVERSIONS__MSG__CEDAR_USE_EXCEPTIONS			"CedarStringConversions with CEDAR_USE_EXCEPTIONS\n"

// MESSAGES FOR THE CLASS CedarValidDate

#define CEDARVALIDDATE__MSG__VERSION						"CedarValidDate was compiled into and object module on "
#define CEDARVALIDDATE__MSG__LOGGING_WITH_CEDARDUMP				"CedarValidDate is LOGGING_WITH_CEDARDUMP\n"
#define CEDARVALIDDATE__MSG__CEDAR_USE_EXCEPTIONS				"CedarValidDate with CEDAR_USE_EXCEPTIONS\n"
#define CEDARVALIDDATE__MSG__WARNING_INCORRECT_HOUR				"Cedar: Warning; An invalid hour value of 24 has been detected but processing is not affected.\n"
#define CEDARVALIDDATE__MSG__WARNING_INCORRECT_MINUTE				"Cedar: Warning; An invalid minute value of 60 has been detected but processing is not affected.\n"
#define CEDARVALIDDATE__MSG__WARNING_INCORRECT_SECOND				"Cedar: Warning; An invalid second value of 6000 has been detected but processing is not affected.\n"

// MESSAGES FOR THE CLASS CedarDate

#define CEDARDATE__MSG__VERSION							"CedarDate was compiled into and object module on "
#define CEDARDATE__MSG__LOGGING_WITH_CEDARDUMP					"CedarDate is LOGGING_WITH_CEDARDUMP\n"
#define CEDARDATE__MSG__CEDAR_USE_EXCEPTIONS					"CedarDate with CEDAR_USE_EXCEPTIONS\n"

// MESSAGES FOR THE CLASS CedarString

#define CEDARSTRING__MSG__MEMORY_ALLOCATION_ERROR				"Cedar: Fatal; memory allocation error.\n"

// MESSAGES FOR THE CLASS CedarConstraintEvaluator

#define CEDARCONSTRAINTEVALUATOR__MSG__MORE_SERVER_SIDE_FUNCTIONS_THAN_MAX_ALLOWED "parse error: more server side functions that max allowed.\n"

#endif // CedarMessages_h_
