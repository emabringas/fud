/**
*  \file:      boinc_constants.h
*  \brief      Header file providing usefull constants
*              System:     FuD
*              Language:   C++
*
*  @author     Lucas Besso     -   E-Mail: lbesso AT gmail.com
*  @author     Raul Striglio   -   E-Mail: rulitox.s AT gmail.com
*
*
*  @Last Update:
*      $Id: boinc_constants.h 409 2011-02-08 14:45:38Z lbesso $
*      $URL: http://fud.googlecode.com/svn/branches/boinc/src/middlewares/boinc/server/common/boinc_constants.h $
*      $LastChangedBy: lbesso $ Author of last commit
*
*
* FuD is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* FuD is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with FuD.  If not, see <http://www.gnu.org/licenses/>.
*/

namespace fud
{

    /** Used to create the Work Units of BOINC. Represents the path where the file which containg the next WU number is placed. */
    const std::string PATH_NUMBER_WU = "download/number_wu";

    /** Define the path where the Workunit template is placed. */
    const std::string WU_TEMPLATE = "templates/fud_wu.xml";

    /** Define the path where the result template is placed. */
    const std::string RE_TEMPLATE = "templates/fud_re.xml";

    /** Define a common length used to define some variables that represents paths. */
    const fud_int PATH_LENGTH = 256;

    /** Define the application name which runs over the fud framework. */
    const std::string NAME_APP = "fud";

    /** Define the sleep time of the assimilator_thread. */
    const fud_uint SLEEP_INTERVAL = 1;

    /** Used to create the Work Unit. Defines the amount of files which will be used like workunit's input file. */
    const fud_uint NRO_INFILES = 1;
  
    /** Represents the correct value that retvals should return. */
    const fud_int RETVAL_OK = 0;
    
    /** Represents the correct values of workunit's fields. */
    const fud_int WU_NO_ERROR = 0;
    
}

