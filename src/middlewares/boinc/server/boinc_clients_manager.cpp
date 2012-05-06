/**
*  \file:      boinc_clients_manager.cpp
*  \brief      Implementation of BoincClientsManager class.
*              System:     FuD
*              Language:   C++
*
*  @author     Lucas Besso     -   E-Mail: lbesso AT gmail.com
*  @author     Raul Striglio   -   E-Mail: rulitox.s AT gmail.com
*
*
*  @Last Update:
*      $Id: boinc_clients_manager.cpp 850 2011-12-12 15:02:09Z lbesso $
*      $URL: https://fud.googlecode.com/svn/branches/boinc/src/middlewares/boinc/server/boinc_clients_manager.cpp $
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

// FuD
#include "boinc_clients_manager.h"
#include "job_manager.h"
#include "boinc_common.h"

// MySQL
#include "errmsg.h"

// BOINC
#include "backend_lib.h"
#include "sched_config.h"
#include "util.h"
#include <str_util.h>
#include "error_numbers.h"


using namespace fud;


BoincClientsManager * BoincClientsManager::_instance = NULL;

BoincClientsManager * BoincClientsManager::get_instance()
{
    if (_instance == NULL)
        _instance = new BoincClientsManager();
    return _instance;
}


BoincClientsManager::BoincClientsManager()
{

}


void BoincClientsManager::boinc_register_client()
{
    // Init the client_proxy.
    boinc_log_debug(std::string("Registering BOINC with FuD."));
    BoincClientProxy * client = new BoincClientProxy();
    client->set_concurrent_jobs(UNLIMITED_JOBS);
    // Register the unique client proxy.
    register_client(client);
}


bool BoincClientsManager::should_resend_job_units()
{
    return false;
}


void BoincClientsManager::post_initialization()
{
    boinc_register_client();
}


BoincClientsManager::BoincClientProxy::BoincClientProxy() :
    ClientProxy(),
    _running_assimilator(true),
    _raii_assimilator_db(_db_assimilator),
    _raii_db_conn(boinc_db)
{
    set_log_level(LOG_HIGH);
    boinc_log_debug(std::string("Parsing the BOINC config file."));
    
    // Read the BOINC config file.
    int retval = config.parse_file();
    if (retval != RETVAL_OK)
    {
        std::string message =  "Can't parse BOINC config.xml file, ";
        message += boincerror(retval);
        throw (BoincFileException(message));
    }

    // Open the BOINC database.
    boinc_log_debug(std::string("Connecting with the BOINC database."));
    retval = boinc_db.open(config.db_name, config.db_host, config.db_user, config.db_passwd);
    if (retval != RETVAL_OK)
    {
        std::string message = "Can't open DB, ";
        message += boincerror(retval);
        throw (BoincDataBaseException(message));
    }

    //Creates assimilator thread to handle client response.
    _assimilator_thread = boost::thread( boost::bind( &BoincClientProxy::assimilator_thread, this ) );
}


void BoincClientsManager::BoincClientProxy::assimilator_thread()
{
    try 
    {
        run();
    }
    catch(const BoincException& e)
    {
        boinc_log_error(e.what());
        throw;
    }
}


BoincClientsManager::BoincClientProxy::~BoincClientProxy() 
{
    _running_assimilator = false;
    _assimilator_thread.join();
}


WorkUnitID BoincClientsManager::BoincClientProxy::get_new_id_wu()
{
    boinc_log_debug(std::string("Generating a new WorkUnitID."));
    WorkUnitID num;
    std::fstream number_wu;
    // Open the file.
    number_wu.open(PATH_NUMBER_WU.c_str(), std::fstream::in);
    if (!number_wu)
    {
        std::string message ("Can't open the file: ");
        message += PATH_NUMBER_WU;
        boinc_log_debug(message);
        // The file doesn't exist, so create the file.
        number_wu.open(PATH_NUMBER_WU.c_str(), std::fstream::out);
        num = 0; // Initialize workunits id by default with cero.
    }
    else
    {
        number_wu >> num;
        num++;

        // Close the file open mode.
        number_wu.close();
        // Open the file write mode.
        number_wu.open(PATH_NUMBER_WU.c_str(), std::fstream::out);
    }
    // Write the number into file.
    number_wu << num << "\n";
    number_wu.close();
    return num;
}


void BoincClientsManager::BoincClientProxy::generate_download_file(const JobUnit& job_unit, std::string& name_input_file)
{

    // Write the job unit message into the new input file generated.
    boinc_log_debug(std::string("New job. Writing the job_unit message to input file of the workunit."));
    // Get the path of the new input file.
    name_input_file = "job_unit_";

    std::stringstream stream;
    stream << job_unit.get_id();
    name_input_file += stream.str();
    
    char path_input_file[PATH_LENGTH];    
    
    // write input file in the download directory.
    config.download_path(name_input_file.c_str(), path_input_file);

    // Create the input file.
    std::ofstream input_file;
    input_file.exceptions ( std::ofstream::failbit | std::ofstream::badbit );
    input_file.open(path_input_file, std::ios::binary);
 
    // Write the full message of the job_unit.
    input_file << job_unit.serialize();
    input_file.close();
}


void BoincClientsManager::BoincClientProxy::create_boinc_work(std::string name_input_file, const char* wu_template)
     throw (BoincWorkException)
{
    DB_WORKUNIT wu;
    
    // Generate the name of the work unit.
    std::string name_wu("fud_wu_");
    std::stringstream nro;
    nro << get_new_id_wu();
    name_wu += nro.str().c_str();

    // Generate the input file for work units.
    strcpy(wu.name, name_wu.c_str());
    const char* input_files[NRO_INFILES];
    input_files[0] = strdup(name_input_file.c_str());

    // Find the app
    DB_APP app = find_app(NAME_APP, boinc_db);

    // Create the work unit.
    boinc_log_debug(std::string("Creating a new workunit."));

    //Clear the workunit's fields
    wu.clear();
    // Update the workunit's fields.
    strcpy(wu.name, name_wu.c_str());
    wu.appid = app.id;
    
    const int retval = create_work(
                 wu,
                 wu_template,
                 RE_TEMPLATE.c_str(),
                 config.project_path(RE_TEMPLATE.c_str()),
                 input_files,
                 NRO_INFILES,
                 config
             );
             
    free((void *) input_files[0]);
     
    if (retval != RETVAL_OK)
    {
        std::string message =  "Error in create_work(): ";
        message += boincerror(retval);
        throw (BoincWorkException(message));
    }
}


void BoincClientsManager::BoincClientProxy::boinc_process(const JobUnit& job_unit) 
                    throw(std::ofstream::failure, BoincAppException, BoincFileException, BoincWorkException )
{
    std::string name_input_file;
    generate_download_file(job_unit,name_input_file);

    // Read the wu_template.
    boinc_log_debug(std::string("Reading the workunit template file"));
    char* wu_template;
    const int retval = read_file_malloc(config.project_path(WU_TEMPLATE.c_str()), wu_template);
    if (retval != RETVAL_OK)
    {
        std::string  description = "Error in read_file_malloc, ";
        description += boincerror(retval);
        throw (BoincFileException(description));
    }

    create_boinc_work(name_input_file, wu_template);
}


/**  Process with exceptions.  */
void BoincClientsManager::BoincClientProxy::process(const JobUnit& job_unit)
{
    try
    {
        _current_id = job_unit.get_id();
        BoincClientsManager::BoincClientProxy::boinc_process(job_unit);
        
    }
    catch(const std::exception& e)
    {
        boinc_log_error(e.what());
        throw;
    }
}


void BoincClientsManager::BoincClientProxy::run() throw(BoincException)
{
    boinc_log_debug(std::string("Starting the assimilator daemon."));
    //  Open a new database's connection separated from the main process.
    const int retval = _db_assimilator.open(config.db_name, config.db_host, config.db_user, config.db_passwd);
    if (retval != RETVAL_OK)
    {
        std::string message = "The assimilator daemon can't open DB: ";
        message += boincerror(retval);
        throw (BoincDataBaseException(message));
    }
    DB_APP app(&_db_assimilator);
    DB_WORKUNIT wu(&_db_assimilator);
    DB_RESULT canonical_result(&_db_assimilator);
    std::stringstream buf();

    app = find_app(NAME_APP, _db_assimilator);
    while(_running_assimilator)
    {
        if (find_work_unit(app, wu) == true)
        {   
            // Found a WU.
            if ( find_cannonical_result(wu,canonical_result) == true ) 
            {
                // Found a Canonical Result.
                assimilate_handler(wu,canonical_result);
                update_wu_state(wu, WuDone);                
            }
        }
        sleep(SLEEP_INTERVAL);
    }
}


DB_APP BoincClientsManager::BoincClientProxy::find_app(const std::string& app_name, DB_CONN& db_conn) throw(BoincAppException)
{
    boinc_log_debug("Looking the application in the database.");

    // Build the query.
    std::stringstream buf;
    buf << "where name='" << app_name.c_str() << "'";

    // Find app in the boinc database.
    DB_APP app(&db_conn);
    const int retval = app.lookup(buf.str().c_str());
    if (retval != RETVAL_OK)
    {
        std::string  message = "Can't find app: ";
        message += boincerror(retval);
        throw (BoincAppException(message));
    }
    return app;
}


bool BoincClientsManager::BoincClientProxy::find_work_unit(const DB_APP& app, DB_WORKUNIT& wu) throw (BoincDataBaseException)
{
    boinc_log_debug("Looking for workunit unassimilated.");

    // Build the query.
    std::stringstream buf;
    buf <<"where appid=" << app.id << " and assimilate_state=" << WuReady;
    
    //Find workunit in the boinc database.
    const int retval = wu.enumerate(buf.str().c_str());
    if (retval != RETVAL_OK) 
    {
        if (retval != ERR_DB_NOT_FOUND)
        {
            std::string message("MySQL Error: ");
            message += boincerror(retval);
            boinc_log_error(message);
            throw (BoincDataBaseException(message));
        }
        boinc_log_debug(std::string ("Workunit not found."));
        return false;
    }
    boinc_log_debug(std::string ("Workunit found."));
    return true;
}


bool BoincClientsManager::BoincClientProxy::find_cannonical_result(DB_WORKUNIT& wu, DB_RESULT& cannonical_result)
{
    // Build the query.
    std::stringstream buf;
    buf << "where id = " << wu.canonical_resultid;

    DB_RESULT result(&_db_assimilator);
    cannonical_result.clear();
    
    result.enumerate(buf.str().c_str());
    const bool found = result.get_id() == wu.canonical_resultid;
        
    if ( found )
    {
        cannonical_result = result;
    }
    else
    {
        /** If no canonical result found and WU had no other errors,
         * something is wrong, e.g. result records got deleted prematurely.
         * This is probably unrecoverable, so mark the WU as having
         * an assimilation error and keep going.
         */
        if (wu.error_mask == WU_NO_ERROR)
        {
            std::string message("Cannonical result not found. Setting wu as WU_ERROR_NO_CANONICAL_RESULT.");
            message += wu.name;
            boinc_log_error(message); // This is considered like an error because it could give a clue of the problem
            wu.error_mask = WU_ERROR_NO_CANONICAL_RESULT;
            buf.str().erase();

            buf << " error_mask="<< wu.error_mask <<std::endl;
            const int retval = wu.update_field(buf.str().c_str());
            if (retval != RETVAL_OK)
            {
                message = "Can't update the workunit field: ";
                message += boincerror(retval);
                boinc_log_error(message);
            }
        }
    }
    return found;
}


void BoincClientsManager::BoincClientProxy::assimilate_handler(DB_WORKUNIT& wu, DB_RESULT& canonical_result)
{
    boinc_log_debug("Starting the assimilation...");
    
    if (wu.canonical_resultid != 0) // The wu has valid cannonical result value.
	{
        FILE_INFO output_file;
        const int retval = get_output_file_info(canonical_result, output_file);
        if (retval == RETVAL_OK)
        {
            try
            {
                std::string* msg = extract_message(output_file);
                ClientsManager::get_instance()->inform_completion( getJobUnitID(), msg);
                //Mandatory order of things! first set status to idle before invoking free_client_event.
                //You risk deadlock otherwise.
                finish_one_job();
                
            }
            catch (const std::exception& ex)
            {
                std::string message ("Can't extract message: ");
                message += ex.what();
                boinc_log_error(message);
            }
        }
        else
        {
            boinc_log_error("Output file wasn't found.");
        }
    }
    else
    {
        throw (BoincWorkException("There isn't canonical result to assimilate."));
    }
}


std::string* BoincClientsManager::BoincClientProxy::extract_message(const FILE_INFO& output_fi) throw(std::fstream::failure, BoincFileException)
{
    boinc_log_debug("Extracting the message from result file.");
    
    char path[PATH_LENGTH];
    const int retval = config.upload_path(output_fi.name.c_str(), path);
    
    if (retval != RETVAL_OK)
    {
        std::string description("Failed uploading path of the file: ");
        description += boincerror(retval);
        boinc_log_error(description);
        throw ( BoincFileException(description) );
    }
    
    std::ifstream ifs_result(path, std::ios::binary);
    ifs_result.exceptions ( std::ofstream::failbit | std::ofstream::badbit );   

    std::stringstream oss;
    oss << ifs_result.rdbuf();
    InputMessage inputMsg(oss.str());
    
    // Get the job unit's id and message
    std::string msg;
    inputMsg >> _current_id >> msg;
   
    std::string *messsage = new std::string(msg.c_str() ,msg.size());
    
    return messsage;
}


void BoincClientsManager::BoincClientProxy::update_wu_state(DB_WORKUNIT& wu, WuState state) throw(BoincDataBaseException)
{
    boinc_log_debug("Updating the state of the workunit.");
    
    //Build the query.
    std::stringstream buf;
    buf << " assimilate_state= " << state;
    //Update wu state.
    const int retval = wu.update_field(buf.str().c_str());

    if (retval != RETVAL_OK) 
    {
        std::string message("Table workunit update failed: ");
        message += boincerror(retval);
        throw (BoincDataBaseException(message));
    }
}    
    
    
namespace fud
{
    ClientsManager* create_clients_manager()
    {
        return BoincClientsManager::get_instance();
    }
}

