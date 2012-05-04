/* $Id: distribution_client.cpp 546 2011-05-09 20:21:42Z marjobe $ */

/** 
 *  @file:      distribution_client.cpp
 *  @details    Implementation file for FuD providing DistributionClient class. \n
 *              System:     FuD                             \n
 *              Language:   C++                             \n
 *              Homepage:   <http://fud.googlecode.com/>
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       January 2011
 *  @version    0.1
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * Copyright (C) 2011 - Mariano Bessone and Emanuel Bringas, FuDePAN.
 *
 * This file is part of FuD
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

#include "distribution_client.h"
#include "processors_manager.h"

#include <boost/thread.hpp>

using namespace fud;

DistributionClient::DistributionClient() :
    _finished(false),
    _message(),
    _message_received(false),
    _message_pending(true),
    _job_queue()
{
    _instance = this;
}

DistributionClient::~DistributionClient()
{
    finish();
}

void DistributionClient::job_listener()
{
    while (!_finished)
    {
        {
            boost::mutex::scoped_lock lock(_job_mutex);
            while( _job_queue.empty() && !_finished )
                _job_in.wait(lock);
        }
        if (!_finished)
        {
            boost::mutex::scoped_lock lock(_job_mutex);

            assert(!_job_queue.empty());
            do_job( _job_queue.front() );
            _job_queue.pop();
        }
    }
}

void DistributionClient::add_job(const InputMessage& message)
{
    boost::mutex::scoped_lock lock(_job_mutex);

    _job_queue.push(message);
    if (_job_queue.size() == 1)
        _job_in.notify_all();
    else
        if (_job_queue.size() > 1)
            std::cerr << "Error: processing more than one job at a time" << std::endl;
}

void DistributionClient::handle_incoming_message(const std::string& in)
{
    set_header_and_message(in);
    if (_header == kJob)
        add_job(_message);
    else
    {
        boost::mutex::scoped_lock lock(_message_mutex);

        _message_received = true;
        _message_in.notify_all();
        _message_pending = false;
    }
}

void DistributionClient::wait_for_message()
{
    boost::mutex::scoped_lock lock(_message_mutex);

    _message_received = false;
    while(!_message_received && _message_pending)
    {
        _message_in.wait(lock);
    }
}

void DistributionClient::finish()
{
    boost::mutex::scoped_lock lock(_job_mutex);

    _finished = true;
    _job_in.notify_all();
}

void DistributionClient::dispatch_and_wait_for_response(const std::string& out)
{
    _message_pending = true;
    dispatch(out);
    wait_for_message();
}

void DistributionClient::do_job(InputMessage& message)
{
    JobUnitID   id;
    std::string body;

    message >> id >> body;

    ProcessorsManager::get_instance()->deliver_message(body);
}

void DistributionClient::set_header_and_message(const std::string& in)
{
    _message.str(in);
    _message >> _header;
}

ServerHeader DistributionClient::header()
{
    return _header;
}

void DistributionClient::message(InputMessage& message)
{
    message = _message;
}
