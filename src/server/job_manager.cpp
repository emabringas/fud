/**
 * \file  job_manager.cpp
 * \brief Implementation file for JobManager class.
 *
 * FuD: FuDePAN Ubiqutous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class DistributableJob.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 * @author     Guillermo Biset
 * @email      billybiset AT gmail.com
 *  
 * @author     Mariano Bessone
 * @email      marjobe AT gmail.com
 *
 * @author     Emanuel Bringas
 * @email      emab73 AT gmail.com
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
 *
 */

#include <syslog.h>
#include <sys/time.h>

#include <boost/bind.hpp>
#include <boost/functional.hpp>

#include "job_manager.h"

namespace fud
{

void finish()
{
    JobManager::destroy();
}

JobManager* JobManager::_instance = NULL; // initialize pointer

JobManager* JobManager::get_instance ()
{
    if (_instance == NULL)  // is it the first call?
    {
        _instance = new JobManager; // create sole instance
    }
    return _instance; // address of sole instance
}

void JobManager::destroy()
{
    delete _instance;
    _instance = NULL;
}

JobManager::JobManager() :
    _clients_manager(create_clients_manager()),
    _producingJobs(),
    _waitingJobs(),
    _jobQueue(),
    _pendingList(),
    _ids_to_job_map(),
    _current_job_unit_size(10), //yes, hardcoded to begin with.
    _status(kStopped),
    _mutex(),
    _event_queue()
{
    timeval tm;
    gettimeofday(&tm, NULL);

    openlog ("FUD", 0, LOG_LOCAL1);
    syslog(LOG_NOTICE,"Started FuD.");

    _clients_manager->set_listener(this);
}

JobManager::~JobManager() 
{
    delete _clients_manager;
    
    stop_scheduler();

    _scheduler_thread.join();
}

DistributableJob* JobManager::jobs_available() //will eventually change policy
{
    if (_producingJobs.empty())
        return NULL;
    else
    {
        DistributableJob* ret = _producingJobs.front();
        _producingJobs.pop_front();
        _producingJobs.push_back(ret);
        return ret;
    }
}

bool JobManager::job_queue_full() //const
{
    return _jobQueue.size() >= MAX_JOBUNITS_QUEUE_SIZE;
}

void JobManager::stop_scheduler()
{
    _event_queue.push(new_event(&JobManagerEventHandler::quit_event));
}

void JobManager::create_another_job_unit()
{
    DistributableJob* job;

    job = jobs_available();
    if ( job != NULL )
    {
        JobUnit* job_unit;
//         job_unit = job->get_next_job_unit(_current_job_unit_size);
        job_unit = job->get_next_job_unit(200);
        if ( job_unit != NULL )
        {
            syslog(LOG_NOTICE,"Job %s created a Job Unit with id %u and size %u.",
                              job->get_name(),job_unit->get_id(),job_unit->get_size());

            _ids_to_job_map[job_unit->get_id()] = job;
            _jobQueue.push_back(job_unit); //just enqueue
        }

        switch( job->get_status() )
        {
            case WaitingMoreData :
                _producingJobs.remove(job);
                _waitingJobs.push_back(job);
                break;
            case FinishedGenerating :
                _producingJobs.remove(job);
                break;
            case ReadyToProduce : break; // Leave it where it is.
        }
    }
}

void JobManager::handle_distributable_job_completed_event(DistributableJob* distjob)
{
    {
        boost::mutex::scoped_lock glock(_mutex);
        _producingJobs.remove(distjob);
        _waitingJobs.remove(distjob);
    }
    handle_new_job_event();
    handle_job_queue_not_full_event();
    handle_free_client_event();
}

void JobManager::free_client_event()
{
    _event_queue.push(new_event(&JobManagerEventHandler::handle_free_client_event));
}

void JobManager::job_unit_completed_event(JobUnitID id)
{
    _event_queue.push(new_event(&JobManagerEventHandler::handle_job_unit_completed_event, id));
}

void JobManager::incoming_message_event(JobUnitID id, fud_uint message_number, std::string* message)
{
    _event_queue.push(new_event(&JobManagerEventHandler::handle_incoming_message_event, id, message_number, message));
}

void JobManager::distributable_job_completed_event(DistributableJob* distjob)
{
    _event_queue.push(new_event(&JobManagerEventHandler::handle_distributable_job_completed_event,distjob));
}

void JobManager::resend_pending_job_unit()
{
    boost::mutex::scoped_lock glock(_mutex);

    if (! _pendingList.empty())
    {
        if ( _clients_manager->assign_job_unit(*_pendingList.front()) )
        {
            // Send this one to the back, act as Round Robin
            _pendingList.push_back(_pendingList.front());
            _pendingList.pop_front();
        }
        else
            syslog(LOG_NOTICE,"Error sending JobUnit %u from Pending List to a client.",_pendingList.front()->get_id());
    }
}

void JobManager::rescue_inclomplete_job_unit(JobUnitID id)
{
    boost::mutex::scoped_lock glock(_mutex);

    if (! _pendingList.empty())
    {
        std::list<JobUnit*>::iterator it;
        it = find_if(_pendingList.begin(),_pendingList.end(),
                    boost::bind(&JobUnit::get_id, _1) == id);

        if (it != _pendingList.end())
        {
            // Enqueue pending job unit founded into job queue to be eventually reasigned.
            _jobQueue.push_back(*it);
            _pendingList.erase(it);
            syslog(LOG_NOTICE,"Info: Job Unit %d Rescued. ",id);
        }
        else
            syslog(LOG_NOTICE,"Info: Job Unit %d is complete or not found. ",id);       
    }
    //TODO assert(complete(JobUnitId) or is_in_job_queue(JobUnitId))
}


void JobManager::handle_free_client_event()
{
    handle_new_job_event();             //check for waiting jobs to see if they can produce
    handle_job_queue_not_full_event();  //check to see if the job queue needs filling
    {
        boost::mutex::scoped_lock glock(_mutex);

        if (_jobQueue.empty())
        {
            #ifdef RESEND_PENDING_JOBS
                resend_pending_job_unit();  //Only for original fud.
            #endif
        }
        else
        {
            if ( _clients_manager->assign_job_unit(*_jobQueue.front()) )
            {
                syslog(LOG_NOTICE,"Sending JobUnit %u to pending list.",(_jobQueue.front()->get_id()) );
                _pendingList.push_back(_jobQueue.front());
                _jobQueue.pop_front();
            }
        }
    }
    handle_job_queue_not_full_event();
}

void JobManager::handle_job_unit_completed_event(JobUnitID id)
{
    boost::mutex::scoped_lock glock(_mutex);
    syslog(LOG_NOTICE,"JobUnit %u completed.",id);

    try
    {
        //generates exception if _ids_to_job_map[id] is not defined
        mili::find(_ids_to_job_map, id)->process_finalization(id);

        //remove from pending list
        std::list<JobUnit*>::iterator it;
        it = find_if(_pendingList.begin(),_pendingList.end(),
                    boost::bind(&JobUnit::get_id, _1) == id);

        if (it != _pendingList.end())
        {
            delete *it;
            _pendingList.erase(it);
        }
        else
        {
            #ifdef RESEND_PENDING_JOBS
                syslog(LOG_NOTICE,"JobUnit %u was already marked as completed.", id);
            #else
                // If RESEND_PENDING_JOBS is OFF and a finished job is not in pending list, then it is a consistency error.
                // This finished job was assigned and there was a mistake removing it from pending list or it never was
                // assigned to nobody and there was a mistake about the JobUnit arrived as finished.
                syslog(LOG_ERR, "ERROR: JobUnit %u is not in the pending list and it was completed !!", id);
                assert(false);
            #endif
        }
    }
    catch(const std::exception& e)
    {
        syslog(LOG_ERR, "Error: %s.", e.what());
    }
}

void JobManager::handle_incoming_message_event(JobUnitID id, fud_uint message_number, std::string* message)
{
    boost::mutex::scoped_lock glock(_mutex);
    syslog(LOG_NOTICE,"JobUnit %u sent a message.", id);

    try
    {
        //generates exception if _ids_to_job_map[id] is not defined
        mili::find(_ids_to_job_map, id)->process_results(id, message_number, message);
    }
    catch(const std::exception& e)
    {
        syslog(LOG_ERR, "Error: %s.", e.what());
    }
    delete message; //release the memory
}

void JobManager::run_scheduler()
{
    syslog(LOG_NOTICE, "Starting scheduler.");
    try
    {
        Event<JobManagerEventHandler>* event;
        while (_status != kStopped)
        {
            event = _event_queue.wait_for_element();
            if (event != NULL)
            {
                event->call(this);
                delete event;
            }
        } /*while*/
    }
    catch(const std::exception& e)
    {
        syslog(LOG_ERR, "Error in scheduler: %s", e.what());
        _status = kStopped;
    }
}

void JobManager::handle_job_queue_not_full_event()
{
    boost::mutex::scoped_lock glock(_mutex);
    while (! job_queue_full() && ! _producingJobs.empty())
        create_another_job_unit();
}

void JobManager::start_scheduler() /*start the scheduler thread, return*/
{
    {
        boost::mutex::scoped_lock glock(_mutex);
        if (_status == kStopped)
        {
            _status = kRunning;
            _scheduler_thread = boost::thread( boost::bind( &JobManager::run_scheduler, this ) );
        }
    }
    handle_new_job_event();
}

void JobManager::handle_new_job_event()
{
    boost::mutex::scoped_lock glock(_mutex);

    if (! _waitingJobs.empty())
    {
        std::list<DistributableJob*>::iterator it = _waitingJobs.begin();
        while (it != _waitingJobs.end())
        {
            if ((*it)->get_status() == ReadyToProduce)
            {
                syslog(LOG_NOTICE, "Starting Job %s", (*it)->get_name());
                _producingJobs.push_back(*it);
                it = _waitingJobs.erase(it);
                free_client_event();
            }
            else
            {
                ++it;
            }
        }
    }
}

void JobManager::quit_event()
{
    boost::mutex::scoped_lock glock(_mutex);
    _status = kStopped;
}

void JobManager::enqueue(DistributableJob* distjob)
{
    boost::mutex::scoped_lock glock(_mutex);
    _waitingJobs.push_back(distjob);
}

}
