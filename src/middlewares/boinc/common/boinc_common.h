/**
*  \file:      boinc_common.h
*  \brief      Common types definition for layer BOINC.
*              System:     FuD
*              Language:   C++
*
*  @author     Lucas Besso     -   E-Mail: lbesso AT gmail.com
*  @author     Raul Striglio   -   E-Mail: rulitox.s AT gmail.com
*
*
*  @Last Update:
*      $Id: boinc_common.h 551 2011-05-20 07:19:21Z lbesso $
*      $URL: https://fud.googlecode.com/svn/branches/boinc/src/middlewares/boinc/common/boinc_common.h $
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

#ifndef BOINC_COMMON_H
#define BOINC_COMMON_H

#include "common.h"
#include "boinc_constants.h"

namespace fud
{
    /** BOINC function output states
    *
    *   \sa BoincClientsManager
    *   \sa BoincDistribution
    */
    enum BoincStatus { ExitStatusOk, ExitStatusError };    
    
}
#endif

