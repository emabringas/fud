/**
 * \file  distributable_job.cpp
 * \brief Implementation file for DistributableJob class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class DistributableJob.
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

#include "fud/common/distributable_job.h"
#include "fud/server/job_manager.h"

using namespace fud;

DistributableJobImplementation::DistributableJobImplementation() :
    _listener(JobManager::get_instance()->get_distributable_job_listener()),
    _completed(),
    _job_units_generated(0),
    _completed_mutex(),
    _job_units_generated_mutex(),
    _input()
{
}


void DistributableJobImplementation::run()
{
    JobManager::get_instance()->enqueue(this); //don't call run twice on the same object
    JobManager::get_instance()->start_scheduler();
}

void DistributableJobImplementation::wait_completion()
{
    boost::unique_lock<boost::mutex> lock(_completed_mutex);

    while(! finished())
        _condition.wait(lock);
}

bool DistributableJobImplementation::finished()
{
    boost::mutex::scoped_lock glock2(_job_units_generated_mutex);

    return get_status() == FinishedGenerating && _completed.size() == _job_units_generated;
}

void DistributableJobImplementation::inform_generation()
{
    boost::mutex::scoped_lock glock(_job_units_generated_mutex);

    ++_job_units_generated;
}

void DistributableJobImplementation::process_results (JobUnitID id, fud_uint message_number, const std::string* message)
{
    if (!completed(id))
    {
        /* Search message */
        bool finded(false);
        std::list<fud_uint>::iterator it;
        for (it = _messages_map[id].begin(); it != _messages_map[id].end() && !finded; it++)
            if (*it == message_number)
                finded = true;
        /* If the message is not in the list: process and add it; otherwise does nothing. */
        if (!finded)
        {
            _input.str(*message);
            handle_results(id,_input);
            _messages_map[id].push_front(message_number);
        }
    }
}

void DistributableJobImplementation::process_finalization (JobUnitID id)
{
    if (!completed(id))
    {
        add_completion(id);
        handle_finalization(id);
        if (finished())
        {
            _condition.notify_all();
            _listener->distributable_job_completed_event(this);
        }
    }
}

JobUnit* DistributableJobImplementation::get_next_job_unit(JobUnitSize  size)
{
    JobUnit* const ju(produce_next_job_unit(size));
    if (ju != NULL)
        inform_generation();

    return ju;
}

void DistributableJobImplementation::add_completion(JobUnitID id)
{
    boost::mutex::scoped_lock glock(_completed_mutex);

    _completed.insert(id);
}

bool DistributableJobImplementation::completed(JobUnitID id)
{
    boost::mutex::scoped_lock glock(_completed_mutex);

    std::set<JobUnitID>::iterator it;
    it = _completed.find(id);

    return it != _completed.end();
}
