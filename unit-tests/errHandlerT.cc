/*******************************************************************
 * TEST CedarErrorHandler
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

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit ;

#include <string>
#include <iostream>
#include <sstream>

using std::cout ;
using std::endl ;
using std::string ;

#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "CedarErrorHandler.h"
#include "CedarArray.h"
#include "CedarLogicalRecord.h"
#include "CedarFile.h"
#include "CedarException.h"
#include "CedarDump.h"

class errHandlerT: public TestFixture {
private:

public:
    errHandlerT() {}
    ~errHandlerT() {}

    void setUp()
    {
    } 

    void tearDown()
    {
    }

    CPPUNIT_TEST_SUITE( errHandlerT ) ;

    CPPUNIT_TEST( do_test ) ;

    CPPUNIT_TEST_SUITE_END() ;

    void do_test()
    {
	cout << endl << "*****************************************" << endl;
	cout << "Entered errHandlerT::run" << endl;

#ifdef CEDAR_USE_EXCEPTIONS
	try
	{
	    CedarErrorHandler::errorT( 99, "sdsis", "This is a double number ", 2.3567, " and this is an integer ", 23567, "\n" ) ;
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch( CedarException &ex )
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 99 ) ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == "Cedar++: This is a double number 2.356700000 and this is an integer 23567\n" ) ;
	}

	cout << "Testing CedarDump class...\n" ;
	try
	{
	    cout << "This should throw exception 50\n" ;
	    if( chdir( "/etc" ) < 0 )
		cout << "Could not change current working directory\n" ;
	    else
		CedarDump dp;
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch (CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 50 ) ;
	    string should_be = (string)"Cedar++: "
	                       + CEDARDUMP__FATAL__OPENING_FILE_BUFFER ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	}

	cout << "Testing CedarArray class...\n" ;
	try
	{
	    cout << "This should throw exception 60\n" ;
	    CedarArray<char> test( 0, 1 ) ;
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch (CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 60 ) ;
	    string should_be = (string)"Cedar++: "
	                       + CEDARARRAY__FATAL__WRONG_SIZE_OR_DELTA ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	}
	try
	{
	    cout<<"This should throw exception 66\n";
	    CedarArray<char> tu(20,0);
	    tu[21]='2';
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch (CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 66 ) ;
	    string should_be = (string)"Cedar++: "
		   + CEDARARRAY__FATAL__CAN_NOT_GROW_ARRAY_WITH_DELTA_ZERO ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	}
	try
	{
	    cout<<"This should throw exception 65\n";
	    CedarArray<char> tu(20,0);
	    tu[-2]='2';
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch (CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 65 ) ;
	    string should_be = (string)"Cedar++: "
			   + CEDARARRAY__FATAL__CAN_NOT_ACCESS_NEGATIVE_INDEX ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	}

	cout<<"Testing CedarFile class...\n"; 
	try
	{
	    cout<<"This should throw exception 90\n";
	    CedarFile f;
	    f.open_file(NULL);
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch (CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 90 ) ;
	    string should_be = (string)"Cedar++: "
	                       + CEDARFILE__FATAL__FILENAME_NULL ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	}
	try
	{
	    cout<<"This should throw exception 100\n";
	    CedarFile f;
	    f.open_file("/bin/ls");
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch (CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 100 ) ;
	    string should_be = (string)"Cedar++: "
	                       + CEDARFILE__FATAL__UNKNOWN_FORMAT ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	}
	try
	{
	    cout<<"This should throw exception 92\n";
	    CedarFile f( 0, CRAY_BLOCKING_FORMAT ) ;
	    f.open_file("/bin/ls");
	    f.get_first_logical_record();
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch (CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 92 ) ;
	    string should_be = (string)"Cedar++: "
	                       + CEDARFILE__FATAL__TYPE_OF_CONTROL ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	}
	try
	{
	    cout << "This should throw exception 101\n" ;
	    CedarFile f ;
	    f.get_next_logical_record() ;
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch (CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 101 ) ;
	    string should_be = (string)"Cedar++: "
	                       + CEDARFILE__FATAL__FILE_NOT_OPEN ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	}

	cout<<"Testing CedarCrayServices class...\n";
	try
	{
	    cout << "This should throw exception 80\n";
	    CedarCrayServices f ;
	    f.get_bit(8,19) ;
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch (CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 80 ) ;
	    string should_be = (string)"Cedar++: "
	                       + CEDARCRAYSERVICES__FATAL__ACCESING_WRONG_BIT ;
	    CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	}

#else

	// this would cause an exit, which would cause the test to fail
	// CedarErrorHandler::errorT(atoi(argv[1]));
	cout << "CEDAR_USE_EXCEPTIONS is not defined, no tests to run" << endl ;

#endif // CEDAR_USE_EXCEPTIONS

	cout << endl << "*****************************************" << endl;
	cout << "Leaving errHandlerT::run" << endl;
    }

} ;

CPPUNIT_TEST_SUITE_REGISTRATION( errHandlerT ) ;

int 
main( int, char** )
{
    CppUnit::TextTestRunner runner ;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() ) ;

    bool wasSuccessful = runner.run( "", false )  ;

    return wasSuccessful ? 0 : 1 ;
}


