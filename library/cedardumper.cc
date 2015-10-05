/*******************************************************************
 * PROGRAM cedardump
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

#include <cstdlib>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <iostream>
#include <vector>

#include "CedarFile.h"
#include "CedarVersion.h"
#include "CedarException.h"
#include "CedarString.h"
#include "CedarDataRecord.h"

using std::cerr ;
using std::cout ;
using std::endl ;
using std::ofstream ;
using std::flush ;
using std::vector ;

const char* NameProgram = 0 ;

void
route_record( const CedarLogicalRecord *pLogRec,
	      streambuf *s1, streambuf *s2,
	      streambuf *s3, streambuf *s4)
{
    pLogRec->save_prologue_header(s4) ;
    if( pLogRec )
    {
	pLogRec->save_prologue(s4);
	switch( pLogRec->get_type() )
	{
	    case 1:
		pLogRec->save_data_buffer(s1);
		break;
	    case 2:
		pLogRec->save_data_buffer(s2);
		break;
	    case 3:
		pLogRec->save_data_buffer(s3);
		break;
	}
    }
}

void
dump_to_stdout( CedarFile &file )
{
    streambuf *gout = cout.rdbuf() ;

    const CedarLogicalRecord *lr = file.get_first_logical_record() ;

    if( lr )
    {
	route_record( lr, gout, gout, gout, gout ) ;
	while( !file.end_dataset() )
	{
	    lr = file.get_next_logical_record() ;
	    if( lr ) 
		route_record( lr, gout, gout, gout, gout ) ;
	}
	return ;
    }
    else 
    {
	cerr << NameProgram << ": can not get a logical record!\n" ;
	return ;
    }
}

void
dump_to_logs( CedarFile &file )
{
    ofstream file_box1( "data_records.log" ) ;
    ofstream file_box2( "catalog_records.log" ) ;
    ofstream file_box3( "header_records.log" ) ;
    ofstream file_box4( "prologue_info.log" ) ;
    streambuf *box1 = file_box1.rdbuf() ;
    streambuf *box2 = file_box2.rdbuf() ;
    streambuf *box3 = file_box3.rdbuf() ;
    streambuf *box4 = file_box4.rdbuf() ;

    const CedarLogicalRecord *lr = file.get_first_logical_record() ;

    if( lr )
    {
	cout << NameProgram << ": dumping to log files ... " << flush ;
	route_record( lr, box1, box2, box3, box4 ) ;
	while( !file.end_dataset() )
	{
	    lr = file.get_next_logical_record() ;
	    if( lr ) 
	    route_record( lr, box1, box2, box3, box4 ) ;
	}
	cout << " done!" << endl ;
	return;
    }
    else 
    {
	cerr << NameProgram << ": can not get a logical record!\n" ;
	return ;
    }
}

void
show_version()
{
    cout << NameProgram << " using libraryCedar: "
         << CedarVersion::get_version_number() << endl
	 << CedarVersion::get_version_info() << endl ;
    exit( 0 ) ;
}

void
show_usage()
{
    cout << NameProgram << " -f [FILE] -s -l -v" << endl ;
    cout << "-f flag is mandatory, FILE is the file to load." << endl ;
    cout << "-k flag retrieves kinst/kindat/parameter information for"
	 << " the specified file" << endl ;
    cout << "-s flags is optional, it sets the checksum per block to be true,"
         << " thus is slower but safer." << endl ;
    cout << "-l flag indicates that this dump must be executed to log files."
         << endl ;
    cout << "-v flag show the version. All other flags are ignored." << endl ;
    exit( 1 ) ;
}


int
execute_request( const char* file,  bool check_sum, bool to_stdout)
{
    try
    {
	CedarFile f( check_sum ) ;
	f.open_file( file ) ;

	if( to_stdout )
	    dump_to_stdout( f ) ;
	else
	    dump_to_logs( f ) ;
    }
    catch( CedarException &e )
    {
	cout << e.get_description() << endl ;
	return e.get_error_code() ;
    }
    catch(...)
    {
	cout << "Unknown exception" << endl ;
	return -1 ;
    }
    return 0 ;
}

vector<int> kinst_list ;
vector<int> kindat_list ;
vector<vector<short int> *> jpar_list ;
vector<vector<short int> *> mpar_list ;

void
handle_kinst( CedarDataRecord *dr )
{
    if( dr )
    {
	int kinst = dr->get_record_kind_instrument() ;
	int kindat = dr->get_record_kind_data() ;

	// grab the jpar variabls, not the values.
	unsigned int jpar_value = dr->get_jpar() ;
	vector<short int> *jpars = new vector<short int>( jpar_value, 0 ) ;
	dr->load_JPAR_vars( *jpars ) ;

	// grab the mpar variabls, not the values.
	unsigned int mpar_value = dr->get_mpar() ;
	vector<short int> *mpars = new vector<short int>( mpar_value, 0 ) ;
	dr->load_MPAR_vars( *mpars ) ;

	// let's see if this new record matches a record we've already
	// saved
	vector<int>::const_iterator kinst_i = kinst_list.begin() ;
	vector<int>::const_iterator kinst_e = kinst_list.end() ;
	vector<int>::const_iterator kindat_i = kindat_list.begin() ;
	vector<vector<short int> *>::const_iterator jp_i = jpar_list.begin() ;
	vector<vector<short int> *>::const_iterator mp_i = mpar_list.begin() ;
	bool found = false ;
	for( ; kinst_i != kinst_e && !found;
	       kinst_i++,kindat_i++,jp_i++, mp_i++ )
	{
	    // compare the kinst
	    if( kinst != (*kinst_i) )
	    {
		continue ;
	    }

	    // compare the kindat
	    if( kindat != (*kindat_i) )
	    {
		continue ;
	    }

	    // compare the number of jpar variables
	    vector<short int> *jpar_vars = (*jp_i) ;
	    if( jpars->size() != jpar_vars->size() )
	    {
		continue ;
	    }

	    // compare the jpar variables, make sure the same set
	    vector<short int>::const_iterator j_i = jpars->begin() ;
	    vector<short int>::const_iterator jv_i = jpar_vars->begin() ;
	    vector<short int>::const_iterator j_e = jpars->end() ;
	    for( ; j_i != j_e; j_i++,jv_i++ )
	    {
		if( (*j_i) != (*jv_i) )
		{
		    continue ;
		}
	    }

	    // compare the number of mpar variables
	    vector<short int> *mpar_vars = (*mp_i) ;
	    if( mpars->size() != mpar_vars->size() )
	    {
		continue ;
	    }

	    // compare the mpar variables, make sure the same set
	    vector<short int>::const_iterator m_i = mpars->begin() ;
	    vector<short int>::const_iterator mv_i = mpar_vars->begin() ;
	    vector<short int>::const_iterator m_e = mpars->end() ;
	    for( ; m_i != m_e; m_i++,mv_i++ )
	    {
		if( (*m_i) != (*mv_i) )
		{
		    continue ;
		}
	    }

	    // everything seems to be the same ... don't need to save
	    // this one
	    found = true ;
	}
	if( !found )
	{
	    // if we didn't find an already existing
	    // kinst/kindat/jpar/mpar set then add this one
	    kinst_list.push_back( kinst ) ;
	    kindat_list.push_back( kindat ) ;
	    jpar_list.push_back( jpars ) ;
	    mpar_list.push_back( mpars ) ;
	}
    }
}

int
read_kinst( const char *file, bool check_sum )
{
    try
    {
	CedarFile f( check_sum ) ;
	f.open_file( file ) ;
	const CedarLogicalRecord *lr = f.get_first_logical_record() ;

	// handle each record that is of type 1, which is a data record.
	// This is why we can cast it to CedarDataRecord.
	if( lr )
	{
	    if( lr->get_type() == 1 )
	    {
		handle_kinst( (CedarDataRecord *)lr ) ;
	    }
	    while( !f.end_dataset() )
	    {
		lr = f.get_next_logical_record() ;
		if( lr ) 
		{
		    if( lr->get_type() == 1 )
		    {
			handle_kinst( (CedarDataRecord *)lr ) ;
		    }
		}
	    }
	}
	else 
	{
	    cerr << NameProgram << ": can not get a logical record!\n" ;
	    return -1 ;
	}

	// display the results to the stdout
	vector<int>::const_iterator kinst_i = kinst_list.begin() ;
	vector<int>::const_iterator kinst_e = kinst_list.end() ;
	vector<int>::const_iterator kindat_i = kindat_list.begin() ;
	vector<vector<short int> *>::const_iterator jp_i = jpar_list.begin() ;
	vector<vector<short int> *>::const_iterator mp_i = mpar_list.begin() ;
	for( ; kinst_i != kinst_e; kinst_i++,kindat_i++,jp_i++,mp_i++ )
	{
	    cout << "kinst " << (*kinst_i)
	         << " - kindat " << (*kindat_i) << endl ;

	    // display the jpar vars
	    vector<short int> *jpars = (*jp_i) ;
	    vector<short int>::const_iterator j_i = jpars->begin() ;
	    vector<short int>::const_iterator j_b = jpars->begin() ;
	    vector<short int>::const_iterator j_e = jpars->end() ;
	    cout << "    jpars: " ;
	    for( ; j_i != j_e; j_i++ )
	    {
		if( j_i != j_b ) cout << ", " ;
		cout << (*j_i) ;
	    }
	    cout << endl ;

	    // display the mpar vars
	    vector<short int> *mpars = (*mp_i) ;
	    vector<short int>::const_iterator m_i = mpars->begin() ;
	    vector<short int>::const_iterator m_b = mpars->begin() ;
	    vector<short int>::const_iterator m_e = mpars->end() ;
	    cout << "    mpars: " ;
	    for( ; m_i != m_e; m_i++ )
	    {
		if( m_i != m_b ) cout << ", " ;
		cout << (*m_i) ;
	    }
	    cout << endl ;
	}
    }
    catch( CedarException &e )
    {
	cout << e.get_description() << endl ;
	return e.get_error_code() ;
    }
    catch( ... )
    {
	cout << "Unknown exception" << endl ;
	return -1 ;
    }
    return 0 ;
}

int
main( int argc, char* argv[] )
{
    NameProgram = argv[0] ;

    bool got_file( false ) ;

    bool to_stdout( true ) ;

    bool get_kinst( false ) ;

    int check_sum = 0 ;

    const char *file = 0 ;

    int c ;

    while( ( c = getopt( argc, argv, "kslvf:" ) ) != EOF )
    {
	switch( c )
	{
	    case 'k':
		get_kinst = true ;
		break ;
	    case 'v':
		show_version() ;
		break ;
	    case 'f':
		file = optarg ;
		got_file = true ;
		break ;
	    case 's':
		check_sum = CEDAR_DO_CHECK_SUM ;
		break ;
	    case 'l':
		to_stdout = false ;
		break ;
	    case '?':
		show_usage() ;
		break ;
	}
    }

    if( get_kinst && got_file )
    {
	return read_kinst( file, check_sum ) ;
    }
    else if( got_file )
    {
	return execute_request( file, check_sum, to_stdout ) ;
    }
    else
    {
	show_usage() ;
	return 1 ;
    }
}

