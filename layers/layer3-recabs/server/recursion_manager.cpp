/* $Id: recursion_manager.cpp 589 2011-07-14 18:25:31Z marjobe $ */

/**
 *  @file:      recursion_manager.cpp
 *  @details    Implementation file for RecursionManager class.
 *              System: RecAbs\n
 *              Language: C++\n
 *
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       August 2010
 *  @version    0.1
 *
 * RecAbs: Recursive Abstraction, an abstraction layer to any recursive
 * process without data dependency for the framework FuD.
 * See <http://fud.googlecode.com/>.
 *
 * Copyright (C) 2010, 2011 - Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of RecAbs project.
 *
 * RecAbs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RecAbs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RecAbs.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <mili/mili.h>
#include <syslog.h>
#include "common.h"
#include "recursion_manager.h"


using namespace recabs;

RecursionManager::RecursionManager(L4ServerApp& app):
    _server_app(app),
    _jobs_waiting_end(0)
{
}

RecursionManager::~RecursionManager()
{
}

void RecursionManager::handle_receive_packet(InputMessage& input)
{
    PacketContainer packet_container;
    RecabsPacketHeader header;
    PacketContainer::iterator it;

    input >> header >> packet_container;
    switch(header)
    {
        case kRes:
            /* For each result, inform to L4 App */
            for (it = packet_container.begin(); it != packet_container.end(); it++)
                _server_app.receive_result(*it);
            break;

        case kJob: 
            /* For each job, it is pushed into the stack */
            for (it = packet_container.begin(); it != packet_container.end(); it++)
                push_child(*it);
            break;

        case kMess:
            /* Delegate message to application*/
            for (it = packet_container.begin(); it != packet_container.end(); it++)
                _server_app.receive_message(*it);
            break;

        default:
            syslog(LOG_NOTICE, "RecAbs: Error receiving message, header does not exist.");      
            break;
    }
}

void RecursionManager::push_child(const Packet& packet)
{
    _stack.push(packet);
}

void RecursionManager::pop_child(Packet& packet)
{
    packet = _stack.top();
    _stack.pop();
    _jobs_waiting_end++;
}

bool RecursionManager::empty_stack() const
{
    return _stack.empty();
}

bool RecursionManager::finished() const
{
    return _jobs_waiting_end == 0 && empty_stack();
}

bool RecursionManager::is_result(const RecabsPacketHeader& header) const
{
    return header == kRes;
}

void RecursionManager::handle_end_of_job()
{
    _jobs_waiting_end--;
}
