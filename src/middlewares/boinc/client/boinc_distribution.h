/**
*  \file:      boinc_distribution.h
*  \brief      Definition of BoincDistribution class.
*              System:     FuD
*              Language:   C++
*
*  @author     Lucas Besso     -   E-Mail: lbesso AT gmail.com
*  @author     Raul Striglio   -   E-Mail: rulitox.s AT gmail.com
*
*
*  @Last Update:
*      $Id: boinc_distribution.h 587 2011-07-07 19:33:24Z rulitox.s@gmail.com $
*      $URL: https://fud.googlecode.com/svn/branches/boinc/src/middlewares/boinc/client/boinc_distribution.h $
*      $LastChangedBy: rulitox.s@gmail.com $ Author of last commit
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
#ifndef BOINC_DISTRIBUTION_H
#define BOINC_DISTRIBUTION_H

#include "common.h"
#include "distribution_client.h"

// BOINC EXCEPTION
#include "boinc_exception.h"


namespace fud
{
    /**
     * The communication part of the client application. Uses BOINC open-source platform.
     *
     * \sa DistributionClient
     */
    class BoincDistribution : public DistributionClient
    {
    public:
        /**
         * Standard constructor.
         *
         * @param argv : is recieved from the main method
         * @param argc : is recieved from the main method
         */
        BoincDistribution(int argc, char** argv);


        /**
        * Start communication. Verify correctness of arguments recieved in the constructor.
        *
        * If the arguments is succesful, it will run the jobs and then will finish.
        *
        */
        virtual void run();
    private:

        BoincDistribution(const BoincDistribution& other);
        
        BoincDistribution& operator= (const BoincDistribution& other);

        virtual void inform_result(bool result);
        
        /** Start BOINC's communication. */
        void boinc_run() throw (std::fstream::failure, BoincFileException, BoincAppException);

        void boinc_inform_result(bool result) throw(std::fstream::failure);

        /**
        * Initialize the communication of client side aplication with the server
        * to begin the computation.
        *
        * @param argc : is recieved from the constructor
        * @param argv : is recieved from the constructor
        */
        void initialize_boinc(int argc, char* argv);

        /** Id of the current job unit */
        JobUnitID _current_id;
        
        /*attr*/
        int             _argc;
        char **         _argv;

    };
}

#endif

