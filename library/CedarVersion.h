/************************************************************************
 * CedarVersion - CedarVersion class declaration.
 *
 ************************************************************************/

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

#ifndef CedarVersion_h_
#define CedarVersion_h_ 1

#include "CedarString.h"

/** @brief Version information for the CEDAR library
*/
class CedarVersion
{
public:
    /** @brief * Returns a string containing the information about the
     * current version of the CEDAR API.
     *
     * The string returned may be treated as a pre formatted text with a
     * detailed explanation of all CEDAR API core components.
     *
     * @returns version information for the CEDAR API
     */
    static string get_version_info() ;

    /** @brief Returns the version string from the CedarConfig.h header file.
     *
     * @returns the CEDAR API version string
     */
    static string get_version_number() ;
};

#endif // CedarVersion_h_

