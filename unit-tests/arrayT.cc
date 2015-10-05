/*******************************************************************
 * TEST CedarArray
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

#include "CedarArray.cc"
#include "CedarException.h"
#include "CedarDump.h"

double ld_count = 0 ;

struct large_data
{
  large_data()
  {
    d1 = d2 = d3 = d4 = d5 = d6 = d7 = d8 = d9 = d10 = ld_count ;
    d11 = d12 = d13 = d14 = d15 = d16 = d17 = d18 = d19 = d20 = ld_count ;
    d21 = d22 = d23 = d24 = d25 = d26 = d27 = d28 = d29 = d30 = ld_count ;
    d31 = d32 = d33 = d34 = d35 = d36 = d37 = d38 = d39 = d40 = ld_count ;
    d41 = d42 = d43 = d44 = d45 = d46 = d47 = d48 = d49 = d50 = ld_count ;
    d51 = d52 = d53 = d54 = d55 = d56 = d57 = d58 = d59 = d60 = ld_count ;
    d61 = d62 = d63 = d64 = d65 = d66 = d67 = d68 = d69 = d70 = ld_count ;
    ld_count++ ;
  }

  double d1;
  double d2;
  double d3;
  double d4;
  double d5;
  double d6;
  double d7;
  double d8;
  double d9;
  double d10;
  double d11;
  double d12;
  double d13;
  double d14;
  double d15;
  double d16;
  double d17;
  double d18;
  double d19;
  double d20;
  double d21;
  double d22;
  double d23;
  double d24;
  double d25;
  double d26;
  double d27;
  double d28;
  double d29;
  double d30;
  double d31;
  double d32;
  double d33;
  double d34;
  double d35;
  double d36;
  double d37;
  double d38;
  double d39;
  double d40;
  double d41;
  double d42;
  double d43;
  double d44;
  double d45;
  double d46;
  double d47;
  double d48;
  double d49;
  double d50;
  double d51;
  double d52;
  double d53;
  double d54;
  double d55;
  double d56;
  double d57;
  double d58;
  double d59;
  double d60;
  double d61;
  double d62;
  double d63;
  double d64;
  double d65;
  double d66;
  double d67;
  double d68;
  double d69;
  double d70;
};

template class CedarArray<large_data>;

typedef CedarArray<char> mar;
class arrayT: public TestFixture {
private:

public:
    arrayT() {}
    ~arrayT() {}

    void setUp()
    {
    } 

    void tearDown()
    {
    }

    CPPUNIT_TEST_SUITE( arrayT ) ;

    CPPUNIT_TEST( do_test ) ;

    CPPUNIT_TEST_SUITE_END() ;

    void do_test()
    {
	cout << endl << "*****************************************" << endl;
	cout << "Entered arrayT::run" << endl;

#ifdef LOGGING_WITH_CEDARDUMP
	CedarDump d;
#endif
	try
	{
	    cout<<"This should report exception 60"<<endl;
	    mar my_array(0,3);
	    CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	}
	catch(CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( ex.get_error_code() == 60 ) ;
	}

	try
	{
	    int i = 0 ;
	    cout << "create array of size 10 with delta 3" << endl ;
	    mar my_array(10,3);
	    CPPUNIT_ASSERT( my_array.get_size() == 10 ) ;
	    CPPUNIT_ASSERT( my_array.get_delta() == 3 ) ;

	    cout << "assign values" << endl ;
	    for( i = 0; i < 10; i++ )
	    {
		my_array[i] = 'a' + i ;
	    }
	    for( i = 0; i < 10; i++ )
	    {
		CPPUNIT_ASSERT( my_array[i] == ('a' + i) ) ;
	    }
	    CPPUNIT_ASSERT( my_array.get_size() == 10 ) ;
	    CPPUNIT_ASSERT( my_array.get_delta() == 3 ) ;

	    cout << "copy array" << endl ;
	    mar my_array1=my_array;
	    CPPUNIT_ASSERT( my_array1.get_size() == 10 ) ;
	    CPPUNIT_ASSERT( my_array1.get_delta() == 3 ) ;
	    for( i = 0; i < 10; i++ )
	    {
		CPPUNIT_ASSERT( my_array1[i] == ('a' + i) ) ;
	    }

	    cout << "enlarge array" << endl ;
	    my_array1[11] = 'k' ;
	    CPPUNIT_ASSERT( my_array1[11] == 'k' ) ;
	    CPPUNIT_ASSERT( my_array1.get_size() == 14 ) ;
	    CPPUNIT_ASSERT( my_array1.get_delta() == 3 ) ;
	}
	catch(CedarException ex)
	{
	    cout << "Reporting exception " << ex.get_error_code()
	         << ": " << ex.get_description() << endl;
	    CPPUNIT_ASSERT( !"exception cought" ) ;
	}

	try
	{
	    cout << "create large_data array" << endl ;
	    CedarArray<large_data> l(20,3);
	    CPPUNIT_ASSERT( l.get_size() == 20 ) ;
	    CPPUNIT_ASSERT( l.get_delta() == 3 ) ;
	    struct large_data &my_data = l[16] ;
	    CPPUNIT_ASSERT( my_data.d1 == 16 ) ;

	    /* This kills the development machine for 64 bit machines
	    try
	    {
		cout << "This should report exception 63" << endl ;
		l.set_size(2123456789);
		CPPUNIT_ASSERT( !"Should have thrown an exception" ) ;
	    }
	    catch(CedarException ex)
	    {
		cout << "Reporting exception " << ex.get_error_code()
		     << ": " << ex.get_description() << endl;
		CPPUNIT_ASSERT( ex.get_error_code() == 63 ) ;
		string should_be = (string)"Cedar++: "
		       + CEDARARRAY__FATAL__EXCEPTION_REPORTED_OPERATOR_NEW ;
		CPPUNIT_ASSERT( (string)ex.get_description() == should_be ) ;
	    }
	    */

	    cout << "copy large_data array" << endl ;
	    CedarArray<large_data> l1;
	    l1=l;
	    struct large_data &my_data1 = l1[16] ;
	    CPPUNIT_ASSERT( my_data1.d1 == 16 ) ;
	}
	catch(CedarException ex)
	{
	    cout<<"Reporting exception "<<ex.get_error_code()<<endl<<endl;
	}

	cout << endl << "*****************************************" << endl;
	cout << "Leaving arrayT::run" << endl;
    }

} ;

CPPUNIT_TEST_SUITE_REGISTRATION( arrayT ) ;

int 
main( int, char** )
{
    CppUnit::TextTestRunner runner ;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() ) ;

    bool wasSuccessful = runner.run( "", false )  ;

    return wasSuccessful ? 0 : 1 ;
}

