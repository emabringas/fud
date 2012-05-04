/**
 * \file  job_manager.cpp
 * \brief Implementation file for JobManager class.
 *
 * FuD: FuDePAN Ubiqutous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class DistributableJob.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
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

using namespace fud;

JobManager* JobManager::_instance = NULL; // initialize pointer

JobManager* JobManager::get_instance ()
{
    if (_instance == NULL)  // is it the first call?
    {
        _instance = new JobManager; // create sole instance
    }
    return _instance; // address of sole instance
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

    openlog ("FUD",NULL, LOG_LOCAL1);
    syslog(LOG_NOTICE,"Started FuD.");

    _clients_manager->set_listener(this);
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
    _status = kStopped;
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

void JobManager::job_unit_completed_event(JobUnitID id, std::string* msg)
{
    _event_queue.push(new_event(&JobManagerEventHandler::handle_job_unit_completed_event, id, msg));
}

void JobManager::distributable_job_completed_event(DistributableJob* distjob)
{
    _event_queue.push(new_event(&JobManagerEventHandler::handle_distributable_job_completed_event,distjob));
}

void JobManager::handle_free_client_event()
{
    handle_new_job_event();             //check for waiting jobs to see if they can produce
    handle_job_queue_not_full_event();  //check to see if the job queue needs filling
    {
        boost::mutex::scoped_lock glock(_mutex);

        if (_jobQueue.empty())
        {
            if (! _pendingList.empty())
            {
                if ( _clients_manager->assign_job_unit(*_pendingList.front()) )
                {
                    //send this one to the back, act as Round Robin
                    _pendingList.push_back(_pendingList.front());
                    _pendingList.pop_front();
                }
                else
                    syslog(LOG_NOTICE,"Error sending JobUnit %u from Pending List to a client.",_pendingList.front()->get_id());
            }
        }
        else
        {
            if ( _clients_manager->assign_job_unit(*_jobQueue.front()) )
            {
                syslog(LOG_NOTICE,"Sending JobUnit %u to pending list.",(_jobQueue.front()->get_id()) );
                _pendingList.push_back(_jobQueue.front());
                _jobQueue.pop_front();
            }
            else
                syslog(LOG_NOTICE,"Error sending JobUnit %u from Job Queue to a client.",_jobQueue.front()->get_id());
        }
    }
    handle_job_queue_not_full_event();
}

void JobManager::handle_job_unit_completed_event(JobUnitID id, std::string* message)
{
    boost::mutex::scoped_lock glock(_mutex);
    syslog(LOG_NOTICE,"JobUnit %u completed.",id);

    try
    {
        //generates exception if _ids_to_job_map[id] is not defined
        mili::find(_ids_to_job_map,id)->process_results(id, message);

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
            syslog(LOG_NOTICE,"Finished JobUnit %u was not in pending list.",id);
    }
    catch(const std::exception& e)
    {
        syslog(LOG_NOTICE,"Error: %s.",e.what());
    }
    delete message; //release the mem
}

void JobManager::run_scheduler()
{
    syslog(LOG_NOTICE,"Starting scheduler.");
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
        syslog(LOG_NOTICE,"Error in scheduler: %s",e.what());
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
            boost::thread thr1( boost::bind( &JobManager::run_scheduler, this ) );
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
                syslog(LOG_NOTICE,"Starting Job %s",(*it)->get_name());
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

void JobManager::enqueue(DistributableJob* distjob)
{
    boost::mutex::scoped_lock glock(_mutex);
    _waitingJobs.push_back(distjob);
}

