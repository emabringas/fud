/**
 * @file  delegator.cpp
 * @brief Implementation file for Delegator class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2012 - Mariano Bessone & Lucas Besso, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class DistributableJob.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 * @author     Mariano Bessone
 * @email      marjobe AT gmail.com
 *
 * @author     Lucas Besso
 * @email      lbesso AT gmail.com
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

#include "delegator.h"

using namespace fud;

Delegator::Delegator( JobManagerListener const * job_manager_listener,
                      ClientsRequestListener const * clients_request_listener ):
    _job_manager_listener(job_manager_listener),
    _clients_request_listener(clients_request_listener)
{}

void Delegator::handle_message(ClientID client_id, const Message& mesage)
{
    /**
     * TODO Implement delegate method.
     * Uses JobManagerListener and ClientRequestsListener to delegate the message depending
     * on the message type.
     */
}

void Delegator::on_idle_client(ClientID client_id)
{
    _job_manager_listener->on_idle_client();
}

void Delegator::on_disconnect_client(ClientID client_id)
{
    _job_manager_listener->on_disconnect_client(client_id);
}

void Delegator::on_arrive_message(ClientID client_id, const Message& message)
{
    /** TODO Extracts the header of the message. */
    handle_message(client_id, header, message_wt_header);
}

