/*******************************************************************
 * TEST CedarConstraintEvaluator
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

#include <string>
#include <iostream>

using std::cout ;
using std::endl ;
using std::string ;

#include "CedarConstraintEvaluator.h"
#include "CedarException.h"

int
main(int argc, char* argv[])
{
  if (argc!=2)
    {
      cout<<"You must supply an argument"<<endl;
      return 1;
    }
  try
    {
      CedarConstraintEvaluator ce;
      ce.parse(argv[1]);
      if (ce.got_signature())
	{
	  string s="The person signing is "; 
	  s+=(string)ce.get_signature();
	  cout<<s<<endl;
	}
      cout<<"parse OK"<<endl;
      CedarArray <field> tp(30,2);
      for (int k=0; k<tp.get_size(); k++)
	tp[k]=k;
      CedarParameter par("17<0");

      if (par.hasUpperBound())
	cout<<"par= "<<par.getValue()<<" U= "<<par.getUpperBound()<<endl;
      else
	if (par.hasLowerBound())
	cout<<"par= "<<par.getValue()<<" L= "<<par.getLowerBound()<<endl;

      if (par.adjustData(tp) )
	{
	  
	  cout<<"New size "<<tp.get_size()<<endl;
	  
	  for (int k=0; k<tp.get_size(); k++)
	    cout<<tp[k]<<",";
	  cout<<endl;
	}
      else
	cout<<"No data"<<endl;
	
    }
  catch(CedarException &ex)
    {
      cout<<ex.get_description()<<endl;
    }
  catch(...)
    {
      cout<<"undefined exception"<<endl;
    }
  return 0;
}
