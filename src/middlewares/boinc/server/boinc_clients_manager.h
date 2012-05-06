/**
*  \file:      boinc_clients_manager.h
*  \brief      Definition of BoincClientsManager class.
*              System:     FuD
*              Language:   C++
*
*  @author     Lucas Besso     -   E-Mail: lbesso AT gmail.com
*  @author     Raul Striglio   -   E-Mail: rulitox.s AT gmail.com
*
*
*  @Last Update:
*      $Id: boinc_clients_manager.h 850 2011-12-12 15:02:09Z lbesso $
*      $URL: https://fud.googlecode.com/svn/branches/boinc/src/middlewares/boinc/server/boinc_clients_manager.h $
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
 
#ifndef BOINC_CLIENTS_MANAGER_H
#define BOINC_CLIENTS_MANAGER_H

#include <list>
#include <fstream>
#include <sstream>

// FuD
#include "clients_manager.h"
#include "job_unit.h"

// BOINC
#include "sched_util.cpp"
#include "validate_util.h"
#include "filesys.h"
#include "sched_msgs.h"

// EXCEPTION
#include "boinc_exception.h"


namespace fud
{

    /** This type represents the workunits states. */
    enum WuState { WuInit = ASSIMILATE_INIT, WuReady = ASSIMILATE_READY, WuDone = ASSIMILATE_DONE };

    /** This type represents the level logs. */
    enum BoincLevel { LOG_LOW = 1, LOG_MIDDLE = 2, LOG_HIGH = 3 };

    typedef fud_uint WorkUnitID;

    /** Log error message for the server app.
    *
    * @param message : The log message.
    */
    inline void boinc_log_error(const std::string& message)
    {
        std::string msg = message;
        msg += "\n";
        log_messages.printf(MSG_CRITICAL, msg.c_str(), NULL);
    }

    /** Log normal message for the server app.
    *
    * @param message : The log message.
    */
    inline void boinc_log_normal(const std::string& message)
    {
        std::string msg = message;
        msg += "\n";
        log_messages.printf(MSG_NORMAL, msg.c_str(), NULL);
    }

    /** Log debug message for the server app.
    *
    * @param message : The log message.
    */
    inline void boinc_log_debug(const std::string& message)
    {
        std::string msg = message;
        msg += "\n";
        log_messages.printf(MSG_DEBUG, msg.c_str(), NULL);
    }

    /** Set the BOINC logs level.
    *
    * @param level : The log level
    */
    void set_log_level(BoincLevel level)
    {
        log_messages.debug_level = level;
    }

   /**
    * The communication part of the server application.
    *
    * \sa ClientsManager
    */
    class BoincClientsManager : public ClientsManager
    {
    
    public:
    
       /** Singleton method */
        static BoincClientsManager * get_instance();

        void boinc_register_client();

        bool should_resend_job_units();
        
        ~BoincClientsManager(){};
        
    private:
        /**
        * Standard constructor 
        *
        */
        BoincClientsManager();
        
        void post_initialization();

       /**
        * A concrete ClientProxy using this distributing middleware.
        *
        * \sa ClientProxy
        */
        class BoincClientProxy : public ClientProxy
        {
        public:
            /**
            * Standard constructor.
            */
            BoincClientProxy();
            
            inline JobUnitID getJobUnitID() { return _current_id; };

            virtual ~BoincClientProxy();
            
        private:
        
            virtual void process(const JobUnit& job_unit);
            
            void boinc_process(const JobUnit& job_unit) throw(std::ofstream::failure, BoincAppException, BoincFileException, BoincWorkException);

            /** Generate the input file into download directory.
            *
            *   @param job_unit : The jobunit to write into the input file
            */
            void generate_download_file(const JobUnit& job_unit, std::string& name_input_file);
            
            /** 
            * Create the boinc workunit to be computed.
            *
            *   @param name_input_file : The workunit's inputfile name
            *   @param wu_template : The BOINC's workunit template
            */
            void create_boinc_work(std::string name_input_file, const char* wu_template) throw (BoincWorkException);
            
            /** Return a new id to generate the name of the new work unit.
            *  @returns New Workunit id
            *  \sa WorkUnitID
            */
            WorkUnitID get_new_id_wu();

            /** This function in charge of running the assimilator thread */
            void assimilator_thread();

            /** Init the functionality of boinc assimilator */
            void run() throw(BoincException);

            /**
            * Search and return the application in the database.
            *
            * @param app_name : Application's name to find
            * @param db_assimilator : Represents the assimilator connection whit the database
            * @returns The application with "name_app" name
            */            
            DB_APP find_app(const std::string& app_name, DB_CONN& db_assimilator) throw(BoincAppException);

            /** Find and return the workunit related with the application.
            *
            * @param app : Workunit's Application
            * @param wu : The workunit to be sended
            * @returns True if workunit associated with application app is found, false if not.
            */
            bool find_work_unit(const DB_APP& app, DB_WORKUNIT& wu) throw (BoincDataBaseException);
        
            /** Find and return the cannonical result related with the workunit.
            *
            * @param wu : The workunit sended
            * @param canonical_result: Output variable to store the cannonical result value
            * @returns : True if there is a cannonical result or False if not
            */
            bool find_cannonical_result(DB_WORKUNIT& wu, DB_RESULT& cannonical_result);

            /** Find and open the output file represented by cannonical result, and then communicates the message to the upper layer.
            *
            * @param wu : The workunit sended
            * @param canonical_result: Concrete cannonical result
            */
            void assimilate_handler(DB_WORKUNIT& wu, DB_RESULT& cannonical_result);

            /** Extract the message encapsulated in the cannonical result. 
            *
            * @param output_fi : Output file received from the client
            * @returns : Return the message saved into the file represented by cannonical result
            */
            std::string* extract_message(const FILE_INFO& output_fi) throw(std::fstream::failure, BoincFileException);

            /** Update the workunit state in the database.
            *
            * @param wu : The workunit sended
            * @param state : New workunit's state
            */
            void update_wu_state(DB_WORKUNIT& wu, WuState state) throw(BoincDataBaseException);


            /* attr.*/
            
            /** This thread simulates the assimilator daemon of boinc. */
            boost::thread _assimilator_thread;
            bool _running_assimilator;
            
            /** Id of the current job unit */
            JobUnitID _current_id;
            
            /** Represents the assimilator's connector to BOINC database */
            DB_CONN _db_assimilator;
            
            /** Use RAII in database connector boinc_db */
            mili::RAII<DB_CONN, &DB_CONN::close> _raii_db_conn;
            mili::RAII<DB_CONN, &DB_CONN::close> _raii_assimilator_db;
        };
        
        static BoincClientsManager * _instance;
    };
    
}

#endif

