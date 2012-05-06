/**
 * \file  client_proxy.cpp
 * \brief Implementation file for ClientProxy class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
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

#include "client_proxy.h"
#include "clients_manager.h"
#include "processing_history.h"

using namespace fud;

ClientID ClientProxy::_last_id = 0;

ClientProxy::ClientProxy() :
    _history(new ProcessingHistory(10)),
    _id(++_last_id),
    _concurrent_jobs(1),
    _current_concurrent_jobs(0)
{
}

ClientProxy::~ClientProxy()
{
}

void ClientProxy::finish_one_job()
{
    if (_concurrent_jobs != UNLIMITED_JOBS) 
    {
        _current_concurrent_jobs--;
        ClientsManager::get_instance()->free_client_event();
    }
    // Not necessary calling to ClientsManager::get_instance()->free_client_event() method when _concurrent_jobs == UNLIMITED_JOBS
}

void ClientProxy::send_to_process(const JobUnit& job_unit)
{
    if (_concurrent_jobs != UNLIMITED_JOBS)
        _current_concurrent_jobs++;
    
    process(job_unit);
}

void ClientProxy::set_concurrent_jobs(fud_uint concurrent_jobs_number)
{
    _concurrent_jobs = concurrent_jobs_number;
}


