/*******************************************************************
 * TEST CedarStringConversions
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

#include "CedarStringConversions.h"

class strConvertT: public TestFixture {
private:

public:
    strConvertT() {}
    ~strConvertT() {}

    void setUp()
    {
    } 

    void tearDown()
    {
    }

    CPPUNIT_TEST_SUITE( strConvertT ) ;

    CPPUNIT_TEST( do_test ) ;

    CPPUNIT_TEST_SUITE_END() ;

    void do_test()
    {
	cout << endl << "*****************************************" << endl;
	cout << "Entered strConvertT::run" << endl;

	int i;
	char result[80];
	double num[10] = {
	    1.98765,
	    12.98765,
	    123.98765,
	    1234.98765,
	    12345.98765,
	    123456.98765,
	    1234567.98765,
	    12345678.98765,
	    123456789.98765,
	    1234567890.98765
	};
	char *num_str[10] = {
	    (char *)"1.987650000",
	    (char *)"12.987650000",
	    (char *)"123.987650000",
	    (char *)"1234.987650000",
	    (char *)"12345.987650000",
	    (char *)"123456.987650000",
	    (char *)"1234567.987650000",
	    (char *)"12345678.987650000",
	    (char *)"123456789.987650007",
	    (char *)"1234567890.987649918"
	};

	for( i = 0; i < 10; i++ )
	{
	   string result_str = CedarStringConversions::dtoa(result,num[i]) ;
	   cout << "number: " << num[i] << endl
	        << "    converted string: " << result_str << endl
		<< "    expected string:  " << num_str[i] << endl ;
	   CPPUNIT_ASSERT( result_str == num_str[i] ) ;
	}

	cout << endl << "*****************************************" << endl;
	cout << "Leaving strConvertT::run" << endl;
    }

} ;

CPPUNIT_TEST_SUITE_REGISTRATION( strConvertT ) ;

int 
main( int, char** )
{
    CppUnit::TextTestRunner runner ;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() ) ;

    bool wasSuccessful = runner.run( "", false )  ;

    return wasSuccessful ? 0 : 1 ;
}

