/**
*  \file:      boinc_distribution.cpp
*  \brief    Implementation of BoincDistribution class.
*              System:     FuD
*              Language:   C++
*
*  @author     Lucas Besso     -   E-Mail: lbesso AT gmail.com
*  @author     Raul Striglio   -   E-Mail: rulitox.s AT gmail.com
*
*
*  @Last Update:
*      $Id: boinc_distribution.cpp 848 2011-12-11 20:00:17Z lbesso $
*      $URL: https://fud.googlecode.com/svn/branches/boinc/src/middlewares/boinc/client/boinc_distribution.cpp $
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

// BOINC API
#ifdef _WIN32
    #include "boinc_win.h"
    #include <winsock.h>
#endif
#include "error_numbers.h"
#include "boinc_api.h"
#include "str_util.h"
#include "diagnostics.h"     // boinc_init_diagnostics()
#include "util.h"            // parse_command_line(), boinc_sleep()

// FuD
#include <iostream>
#include <fstream>
#include "boinc_distribution.h"
#include "processors_manager.h"
#include "boinc_common.h"



using namespace fud;


// Represents the name of boinc's output file.
const std::string OUTPUT_FILE_NAME = "out.txt";

BoincDistribution::BoincDistribution(int argc, char** argv) :
    DistributionClient(),
    _argc(argc),
    _argv(argv)
{
}


void BoincDistribution::boinc_inform_result(bool result) throw(std::fstream::failure)
{
    if (result)
    {
        std::clog << "FuD: writing result message in output file." << std::endl;
        
        std::string file_name;
        boinc_resolve_filename_s(OUTPUT_FILE_NAME.c_str(), file_name);
        
        std::string body = ProcessorsManager::get_instance()->get_return_message();
        
        OutputMessage bos;
        bos << _current_id << body;

        // File to upload to server.
        std::ofstream out;
        
        //enable the exceptions
        out.exceptions ( std::ofstream::failbit | std::ofstream::badbit );
        out.open(file_name.c_str(), std::ios::binary);
        
        // Get the message with result of computation to send back to server.
        out << bos.str();
    }
}


void BoincDistribution::inform_result(bool result)
{
    try
    {
        boinc_inform_result(result);
    }
    catch(const std::exception& e)
    {
        std::clog << "FuD: " << e.what() << std::endl;
    }
}



void BoincDistribution::boinc_run() throw (std::fstream::failure , BoincFileException, BoincAppException)
{
    // Before initializing BOINC itself, intialize diagnostics, so as to get stderr output
    // to the file stderr.txt, and thence back home.
    boinc_init_diagnostics(BOINC_DIAG_REDIRECTSTDERR |
                           BOINC_DIAG_MEMORYLEAKCHECKENABLED |
                           BOINC_DIAG_DUMPCALLSTACKENABLED |
                           BOINC_DIAG_TRACETOSTDERR);

    std::clog << "FuD: starting FuD computation." << std::endl;
        
    // Initialises a BOINC application.
    // Applications must call this before calling other BOINC functions.
    int retval = boinc_init();
    if (retval != RETVAL_OK)
    {
        std::string message = boincerror(retval);
        throw(BoincAppException(message));
    }

    std::string file_name;

    // Gets the input file name and store it in file_name.
    retval = boinc_resolve_filename_s(_argv[1], file_name);
    if (retval != RETVAL_OK)
    {
        std::string message = "Can't resolve the file name: ";
        message += _argv[1];
        message += ". ";
        message += boincerror(retval);
        throw(BoincFileException(message));
    }

    std::ifstream ifs(file_name.c_str(), std::ios::binary);
    // Enable file exceptions.
    ifs.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);

    std::clog << "FuD: extracting the input file for computation." << std::endl;
        
    // Extract the content of the input file to deliver.
    std::stringstream oss;
    oss << ifs.rdbuf();
    InputMessage input_msg (oss.str() );

    // Get the message and _current_id
    std::string message;
    input_msg >> _current_id >> message;

    ProcessorsManager::get_instance()->deliver_message( message );
    ifs.close();
    boinc_finish( ExitStatusOk );
}


void BoincDistribution::run()
{
    try
    {
        boinc_run();
    }
    catch (const std::exception &e )
    {
        std::clog << "FuD: " << e.what() << std::endl;
        // Invoked to boinc_finish() method to exit the program to tell.
        // the core client the application is exiting with an "unrecoverable error." 
        boinc_finish( ExitStatusError );
    }
}


namespace fud
{
    DistributionClient* create_distribution_client(int argc, char** argv)
    {
        return new BoincDistribution(argc, argv);
    }
}

